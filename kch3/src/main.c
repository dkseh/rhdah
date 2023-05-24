//-------| src/main.c |-------//
#include "main.h"

#define INPUT_GREEN		1
#define INPUT_RED		2
#define INPUT_EXIT		0

static off_t IEB_DOT[MAX_DOT] = {
	IEB_DOT1,
	IEB_DOT2,
	IEB_DOT3,
	IEB_DOT4,
	IEB_DOT5
};
static off_t IEB_FND[MAX_FND] = {
	IEB_FND0,
	IEB_FND1,
	IEB_FND2,
	IEB_FND3,
	IEB_FND4,
	IEB_FND5,
	IEB_FND6,
	IEB_FND7
};
static int total;
static int fd;
static int input_int;
static int map_counter = 0;
static void * map_data[100];
//static seclection_t sel; 
char name[10];
char student_id[9];
int try, ball, strike;

int passwd[4];
int userans[4];
int key_count, key_value;

error_t checker(int argc, char* argv[]);

char trial[10] = {0x00, };

int main(int argc, char* argv[]) {
	char num[10];
	int i;
	short * led, * dot[MAX_DOT], * fnd[MAX_FND];
	short * clcd_cmd, * clcd_data, * keypad_out, * keypad_in;
	
	fd = open("/dev/mem", O_RDWR|O_SYNC);
	if (fd == -1) {
		fprintf(stderr, "Cannot open /dev/mem file");
		exit(EXIT_FAILURE);
	}
	
	led = mapper(IEB_LED, PROT_WRITE);
	for( i=0; i<MAX_DOT; i++ ) {
		dot[i] = mapper(IEB_DOT[i], PROT_WRITE);
	}
	for( i=0; i<MAX_FND; i++ ) {
		fnd[i] = mapper(IEB_FND[i], PROT_WRITE);
	}
	clcd_cmd  = mapper(IEB_CLCD_CMD, PROT_WRITE);
	clcd_data = mapper(IEB_CLCD_DATA, PROT_WRITE);
	keypad_out  = mapper(IEB_KEY_W, PROT_WRITE);
	keypad_in = mapper(IEB_KEY_R, PROT_READ);
	
	init_led(led);
	init_dot(dot);
	init_fnd(fnd);
	init_clcd(clcd_cmd, clcd_data);
	init_keypad(keypad_out, keypad_in);

	if( checker(argc, argv) == ERROR ) {
		error();
	}
	else {
		while( menu() == TRUE ) {	}
	}
	
	unmapper();
	close(fd);
	return 0;
}

short * mapper(off_t offset, int prot) {
	map_data[map_counter] = mmap(NULL, sizeof(short), prot, MAP_SHARED, fd, offset);
	if ( map_data[map_counter] == MAP_FAILED ) {
		fprintf(stderr, "Cannot do mmap()");
		emergency_closer();
	}
	return (short *)map_data[map_counter++];
}

void unmapper() {
	int i;
	for( i=0; i<map_counter; i++) {
		munmap(map_data[i], sizeof(short));
	}
	map_counter = 0;
}

void emergency_closer() {
	unmapper();
	close(fd);
	exit(EXIT_FAILURE);
}

void error(){
    clcd_clear_display();
    clcd_set_DDRAM(0x40);
    clcd_write_string("   !! ERROR !!");
}

error_t checker(int argc, char* argv[]) { // 학번, 사용자 이름 입력
	int S=0;
	if( argc <= 1 ) {
		return ERROR;
	}
	else if( argc >= 2 ) {
			clcd_entry_mode_set(1, S);
			
			clcd_set_DDRAM(0x00);
			clcd_write_string(argv[1]);
			if( argc >= 3 ) {
				clcd_set_DDRAM(0x40);
				clcd_write_string(argv[2]);
			}
	 	strcpy(name, argv[1]);
	 	strcpy(student_id, argv[2]);
		}
		else { return ERROR; }
	return SUCCESS;
}

void random_ans(int * ans) {
	int i, j;
	for (i = 0; i < 5; i++) { //중복 숫자 방지
		ans[i] = (time(NULL) % 10);
		for (j = 0; j < i; j++) {
			if (ans[i] == ans[j]) {i--;}
		}
	}
}

void enter_ans(int * ans) {
	int i;

    for(i = 0; i < 4; i++) {
		clcd_clear_display();
		clcd_set_DDRAM(0x00);
		clcd_write_string("Enter answer");
		clcd_set_DDRAM(0x40);
			
		switch(i) {
				case 0:
					clcd_write_string("First Number");
					break;
				case 1:
					clcd_write_string("Second Number");
					break;
				case 2:
					clcd_write_string("Third Number");
					break;
				case 3:
					clcd_write_string("Fourth Number");
					break;
		}
			
		while(1) {
			key_count=keypad_read(&key_value);
			if(key_count==1){
				ans[i]=key_value;
				buf[i]=ans[i]+'0';
				key_count=0;
				break;
		    }
		}
	}
}

int decimal_check(int * ans) { //0~9까지 입력했는지 체크
    if((ans[0]) > 9 || (ans[1]) > 9 || (ans[2]) > 9 || (ans[3]) > 9) {return 1;}
    else {return 0;}
}
int repeat_check(int * ans) { //중복 숫자 입력 체크
	if((ans[0] == ans[1]) || (ans[0] == ans[2]) || (ans[0] == ans[3]) || (ans[1] == ans[2]) || (ans[1] == ans[3]) || (ans[2] == ans[3])) {
		return 1;
	}
	else {return 0;}
}

void input_mode() {//키패드를 통해 4자리 숫자 입력
	int i, j;
		
	try = 0;
	printf("%d%d%d%d\n",passwd[0], passwd[1], passwd[2], passwd[3]);

	fnd_clear();
	fnd_write(5, 6);
	fnd_write(8, 3);
	fnd_write(0, 0);
	
	while(1) {
		ball=0;
		strike=0;
		
        enter_ans(userans);

		try++;
		dot_write(try);

		for(i = 0; i < 4; i++) {
			for(j = 0; j < 4; j++) {
				if(passwd[i] == userans[j]) {
					if(i==j) {strike++;}
					else {ball++;}
				}
			}
		}

		usleep(50000);
		clcd_clear_display();
		clcd_set_DDRAM(0x00);
		clcd_write_string("Your Answer");
		clcd_set_DDRAM(0x40);
		clcd_write_string(buf);
		sleep(5);

        if(decimal_check(userans)) {
            clcd_clear_display();
			clcd_set_DDRAM(0x00);
			clcd_write_string("Enter number");
			clcd_set_DDRAM(0x40);
			clcd_write_string("smaller than 10");
			sleep(3);
			continue;
        }

		if(repeat_check(userans)) {
			clcd_clear_display();
			clcd_set_DDRAM(0x00);
			clcd_write_string("Number repeated");
			clcd_set_DDRAM(0x40);
			clcd_write_string("Try again");
			sleep(3);
			continue;
		}

		if(strike == 0 && ball == 0) {fnd_write(1, 1);}
		else {fnd_write(0, 1);}
				
		if(strike == 4) {break;}
		else {
			clcd_clear_display();
			clcd_set_DDRAM(0x00);
			clcd_write_string("Wrong answer");
			clcd_set_DDRAM(0x40);
			clcd_write_string("Try again");
			fnd_write(strike, 7);
			fnd_write(ball, 4);
			sleep(3);
		}
	}
}

void gameplay(int players) {
	int i;

	clcd_clear_display();
	clcd_set_DDRAM(0x40);

    switch(players) {
        case 1:
            clcd_write_string("   single play");
            sleep(2);

            led_green();
            fnd_clear();

            printf("\n");
	        printf("**********************************************\n");
	        printf("*                 singleplay start!          *\n");
	        printf("**********************************************\n\n");

 	        random_ans(passwd);
            break;
        case 2:
            clcd_write_string("    multi play");
	        sleep(2);

	        led_green();
	        fnd_clear();
	
	        printf("\n");
	        printf("**********************************************\n");
	        printf("*                 multiplay start!           *\n");
	        printf("**********************************************\n\n");

 	        enter_ans(passwd);

			clcd_clear_display();
			clcd_set_DDRAM(0x00);
			clcd_write_string("Answer saved");
			sleep(3);
            break;
    }

	input_mode();

	dot_clear();
	led_clear();
	
	clcd_clear_display();
	clcd_set_DDRAM(0x00);
	clcd_write_string("Correct answer!");
	clcd_set_DDRAM(0x40);
	clcd_write_string("Trial: ");
	sprintf(trial, "%d", try);
	clcd_write_string(trial);

	for(i=0;i<8;i++) {	
	led_green();
	usleep(50000);
	led_red();
	usleep(50000);
	}
}

truth_t menu() {
	int mode;
	printf("\n");
	printf("***************************************\n");
	printf("*     Please type a number            *\n");
	printf("*     1 : single player               *\n");
	printf("*     2 : 2 players                   *\n");
	printf("*     0 : EXIT                        *\n");
	printf("***************************************\n\n");
	scanf("%d", &mode);
	
	switch(mode) {
		case 1 :
			gameplay(1);
			break;
		case 2 :
			gameplay(2);
			break;
		case 0 :
			clcd_clear_display();
			led_clear();
			fnd_clear();
			return FALSE;
		default :
			break;
	}
	return TRUE;
}
