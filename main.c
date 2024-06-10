#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <string.h>
#include <time.h>

char name[20];
char pass[20];
char num[11];
char mode[6];
	
struct item{
	int quantity;
	char name[20];
	int price;
};

void intro();	
void account_login();
void print_header();
int valid_acc();
void create_acc();
void print_menu();
float check_voucher();
int valid_vouch(char []);
void gotoline(int, int);
char* get_item(int);
int get_price(int);
int take_order(struct item *);
float payment(char*);
void print_bill(struct item* , int, float, char*);
void print_layout(int );
void printn(int);
void print(char[]);
void give_voucher(int);
void loading();

int main(){
	char choice, pay[35]={"\0"};	
	struct item *order= (struct item*)calloc(18,sizeof(struct item));
	int itemsordered;
	float discount=0;
	
	HANDLE  hConsole;
	system("COLOR F0");
	intro();
	system("cls");
	printf("=============================================== WELCOME TO ABC RESTURANT ============================================\n");
	gotoline(43,3);
	printf("Are you already a customer[Y/N]: ");
	fflush(stdin);
	scanf("%c", &choice);
	while(choice!='Y' && choice!='y' && choice!='N' && choice!='n'){
		gotoline(43,4);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 252);
		printf("invalid input, Enter again:   \b\b");
		scanf("%c", &choice);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
	}
	if (choice=='Y' || choice=='y'){
		account_login();
		strcpy(mode,"YOUR");
	}
	else if (choice=='N' || choice=='n'){
		gotoline(43,4);
		printf("Do you want to create an account[Y/N]: ");
		fflush(stdin);
		scanf("%c", &choice);
		while(choice!='Y' && choice!='y' && choice!='N' && choice!='n'){
			gotoline(43,5);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 252);
			printf("invalid input, Enter again:   \b\b");
			scanf("%c", &choice);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
		}
		if (choice=='Y' || choice=='y'){
			create_acc();
			account_login();
			strcpy(mode,"YOUR");
		}
		else if (choice=='N' || choice=='n'){
			strcpy(name,"Customer2701");
			strcpy(num,"--");
			strcpy(mode,"GUEST");
		}
	}
	
	itemsordered=take_order(order);
	discount+=payment(pay);
	discount+= check_voucher();
	loading();
	print_bill(order, itemsordered, discount, pay);
}

void gotoline(int x, int y){
	COORD pos={x,y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}

void intro(){
	gotoline(40,5);
	print("PROGRAMMING FUNDAMETALS PROJECT");
	gotoline(43,7);
	print("RESTURANT BILLING SYSTEM");
	gotoline(40,9);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 248);
	printf("Group members: ");
	gotoline(40,10);
	printf("- Asfandyar Khanzada 22K-4626");
	gotoline(40,11);
	printf("- Ibrahim Ahmed 22K-4341");
	gotoline(40,12);
	printf("- M.Anas Malik 22K-4548");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
	printf("\npress any key to continue......");
	getchar();
}

void account_login(){
	int i=2, index=0;
	char ch;
	system("cls");
	printf("=============================================== WELCOME TO ABC RESTURANT ============================================\n\n");
	while(1){
		gotoline(49,i);
		printf("ACCOUNT LOGIN");
		gotoline(49,i+1);
		printf("Name: ");
		scanf("%s", name);
		gotoline(49,i+2);
		printf("Password: ");
		do{
			ch=getch();
			if(ch=='\r')
				break;
			if(ch!='\b'){
				pass[index++]= ch;
				printf("*");	
			}
			else{
				pass[index--]='\0';
				printf("\b \b");
			}
		}while(1);
		pass[index]='\0';

		if (valid_acc()){
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 249);
			gotoline(49,i+3);
			printf("Login successful\n");	
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
			Sleep(1000);
			break;
		}
			system("cls");
			printf("=============================================== WELCOME TO ABC RESTURANT ============================================\n\n");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 252);
			gotoline(49,2);
			printf("Invalid account details\n");
			i=3;	
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);		
	}
}

int valid_acc(){
	char fname[20], fpass[20];
	FILE *file;
	file= fopen("accounts.txt","r");
	while(fscanf(file ,"%s %s %s", fname, fpass, num)==3){
		if(!(strcmp(name,fname) || strcmp(pass,fpass))){
			fclose(file);
			return 1;
		}
	}
	fclose(file);
	return 0;
}

void create_acc(){
	char fnum[20]={"a"}, fname[20], fpass[20]={"a"};
	FILE *ptr;
	ptr= fopen("accounts.txt","a");
	system("cls");
	printf("=============================================== WELCOME TO ABC RESTURANT ============================================\n\n");
	gotoline(49,2);
	printf("ENTER YOUR DETAILS");
	gotoline(49,3);
	printf("Your name: ");
	scanf("%s", fname);
	gotoline(49,4);
	printf("Password: ");
	scanf("%s", fpass);
	gotoline(49,5);
	printf("Phone number: ");
	scanf("%s", fnum);
	fprintf(ptr ,"\n%s %s %s", fname, fpass, fnum);
	fclose(ptr);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 249);
	gotoline(49,6);
	printf("Account created successful. Now login\n");	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
	Sleep(1000);
}

void print_menu(){
	gotoline(52,3);
	printf(" -----MENU-----");
	gotoline(51,5);
	printf("----APPETIZERS----");
	gotoline(33,7);
	printf("1.DYNAMITE SHRIMPS RS.1000\t2.CHICKEN WINGS RS.600");
	gotoline(33,9);
	printf("3.MOZARELLA STICKS RS.900\t4.FRENCH FRIES RS.300");
	gotoline(51,11);
	printf("---MAIN COURSES---");
	gotoline(33,13);
	printf("5.TARAGON CHICKEN RS.1500\t6.BEEF STEAK RS.2000");
	gotoline(33,15);
	printf("7.CHICKEN PIZZA RS.1200\t8.CLUB SANDWICH RS.800");
	gotoline(33,17);
	printf("9.ALFREDO PASTA RS.1400\t10.AMERICAN BURGER RS.950");
	gotoline(51,19);
	printf("----BEVERAGES ----");
	gotoline(33,21);
	printf("11.MINT LEMONADE RS.450\t12.PINA COLADA RS.600");
	gotoline(33,23);
	printf("13.SOFT DRINK RS.250\t\t14.MINERAL WATER RS.150");
	gotoline(51,25);
	printf("-----DESSERTS-----");
	gotoline(33,27);
	printf("15.LAVA CAKE RS.1000\t\t16.VANILLA ICECREAM RS.500");
	gotoline(33,29);
	printf("17.RESBERRY CHEESECAKE RS.900\t18.PINEAPPLE TART RS.1200");
}

float check_voucher(){
	char code[6], choice;
	float dis;
	print_header();
	gotoline(45,3);	printf("Do you have a voucher[Y/N]: ");
	fflush(stdin);
	scanf("%c", &choice);
	while(choice!='Y' && choice!='y' && choice!='N' && choice!='n'){
		gotoline(45,4);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 252);
		printf("invalid input, Enter again:   \b\b");
		scanf("%c", &choice);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
	}
	if (choice=='N' || choice=='n'){
		return 0;
	}
	gotoline(45,4);
	printf("Enter voucher code:           ");
	fflush(stdin);
	gotoline(65,4);
	scanf("%s", code);
	if(valid_vouch(code)){
		switch(code[0]){
			case 'E': dis= 0.15; break;
			case 'F': dis= 0.1; break;
			case 'G': dis= 0.05; break;
			case 'H': dis= 0.025; break;
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 242);
		gotoline(45,5);
		printf("Congragulations!! You got %.1f%% off\n", dis*100);		
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
		Sleep(1000);
		return dis;
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 252);
	gotoline(45,5);
	printf("Sorry, invalid voucher");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);		
	Sleep(1000);
}

int valid_vouch(char code[]){
	char fcode[6];
	int flag=0;
	FILE *file;
	file= fopen("vouchers.txt", "r");
	while(fscanf(file, "%s", fcode)==1)
		if(strcmp(code,fcode)==0){
			flag=1;
		}
	fclose(file);
	return flag;
}

void print_header(){
	system("cls");
	printf("=============================================== WELCOME TO %s ACCOUNT ============================================\n", mode);
	printf("  name: %s\n", name);
	printf("  phone no.: %s\n", num);
}

char* get_item(int itemno){
	switch(itemno){
		case 1: return "DYNAMITE SHRIMPS";
		case 2: return "CHICKEN WINGS";
		case 3: return "MOZARELLA STICKS";
		case 4: return "FRENCH FRIES";
		case 5: return "TARAGON CHICKEN";
		case 6: return "BEEF STEAK";
		case 7: return "CHICKEN PIZZA";
		case 8: return "CLUB SANDWICH";
		case 9: return "ALFREDO PASTA";
		case 10: return "AMERICAN BURGER";
		case 11: return "MINT LEMONADE";
		case 12: return "PINA COLADA";
		case 13: return "SOFT DRINK";
		case 14: return "MINERAL WATER";
		case 15: return "LAVA CAKE";
		case 16: return "VANILLA ICECREAM";
		case 17: return "RESBERRY CHEESECAKE";
		case 18: return "PINEAPPLE TART";
	}
}

int get_price(int itemno){
	switch(itemno)
	{
		case 1: return  1000;
		case 2: return  600;
		case 3: return  900;
		case 4: return  300;
		case 5: return  1500;
		case 6: return  2000;
		case 7: return  1200;
		case 8: return  800;
		case 9: return  1400;
		case 10: return 950;
		case 11: return 450;
		case 12: return 600;
		case 13: return 250;
		case 14: return 150;
		case 15: return 1000;
		case 16: return 500;
		case 17: return 900;
		case 18: return 1200;
	}
}

int take_order(struct item *order){
	int j=0,itemno , i=0, quantity=0;
	char opt;
	while(1){
		print_header();
		print_menu();
		gotoline(0,31);
		printf("---------------------------------------------------------------------------------------------------------------------");
		gotoline(42,32);
			printf("------------Welcome %s------------", name);
		if(i==0)
			do{
				gotoline(44,33);
				printf("ARE YOU READY TO ORDER?(Y/N):  \b");
				fflush(stdin);
				scanf(" %c",&opt);
				while(opt!='Y' && opt!='y' && opt!='N' && opt!='n'){
					gotoline(44,34);
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 252);
					printf("invalid input, Enter again:   \b\b");
					scanf("%c", &opt);
					gotoline(44,34);
					printf("                                ");
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
				}
			}while(opt=='n'||opt=='N');
			
		gotoline(38,33);
		printf("ENTER YOUR ORDER:              ");
		gotoline(38,34);
		printf("Enter 0 to place order");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 242);
		gotoline(68,33);
		printf("Items ordered: %d", quantity);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
		gotoline(38,36);
		printf("Item number: ");
		scanf("%d", &itemno);
		if(itemno==0)
			break;
		while( (itemno>18) || (itemno<1) ){
			gotoline(38,36);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 252);
			printf("Invalid item number, Enter again:   \b\b");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
			fflush(stdin);
			scanf("%d", &itemno);
		}
		strcpy((order+i)->name, get_item(itemno));
		(order+i)->price= get_price(itemno);
		gotoline(38,36);
		printf("%s                           ", (order+i)->name);
		gotoline(38,37);
		printf("Quantity: ");
		scanf("%d", &((order+i)->quantity));
		quantity+=(order+i)->quantity;
		if((order+i)->quantity==0){
			system("cls");
			continue;
		}
		i++;
		system("cls");
	}
	order=realloc(order, i*sizeof(struct item));
	
	print_header();
	gotoline(43,4);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 249);
	print("YOUR ORDER PLACED SUCCESSFULLY!!");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
	Sleep(1000);
	return i;
}

float payment(char* ret){
	int opt;
	char number[18];
	
	system("cls");
	print_header();
	
	gotoline(50,3);
	printf("----PAYMENT----");
	gotoline(45,5);
	printf("1. CASH");
	gotoline(45,6);
	printf("2. CARD");
	gotoline(45,7);
	printf("3. ONLINE");
	gotoline(40,8);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 248);
	printf("5%% off is offered on all cashless payments");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
	gotoline(42,10);
	printf("Select mode of payment: ");
	fflush(stdin);
	scanf("%d", &opt);
	while(opt<1 || opt>3){
		gotoline(42,10);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 252);
		printf("Invalid option, select again: ");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
		fflush(stdin);
		scanf("%d", &opt);
	}
	
	switch(opt){
		case 1: 
			gotoline(42,10);  
			printf("   Cash...                     ");
			strcat(ret,"Payment method: Cash");
			Sleep(500);
			return 0;
		case 2: 
			gotoline(42,10);
			printf("Enter your card number(upto 17 digits): ");
			gotoline(42,11);
			scanf("%s", number);
			while(strlen(number)>17){
				gotoline(42,10);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 252);
				printf("Invalid input. Re-enter your card number(upto 17 digits): ");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
				gotoline(42,11);
				scanf("%s", number);	
			}
			strcpy(ret,"Card number: ");
			strcat(ret, number);
			Sleep(500);
			return 0.05;
		case 3: 
			gotoline(42,10);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 252);
			printf("Invalid input. Re-enter your card number(upto 17 digits): ");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
			gotoline(42,11);
			scanf("%s", number);
			while(strlen(number)>17){
				gotoline(42,10);
				printf("Invalid input. Re-enter your card number(upto 17 digits): ");
				gotoline(42,11);
				scanf("%s", number);	
			}
			strcpy(ret,"Accout number: ");
			strcat(ret, number);
			Sleep(500);
			return 0.05;
	}		
}

void print_bill(struct item* order, int items, float discount, char* pay){
	int i, saved, total=0;
	time_t t;
	time(&t);
	print_header();
	print_layout(items);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	give_voucher(items);
	gotoline(47,7);
	print(name);
	gotoline(46,8);
	print(num);
	gotoline(32,9);
	print(pay);
	for(i=0;i<items; i++){
		gotoline(32,13+i+i);
		Sleep(100);
		printf("%d",(order+i)->quantity);
		gotoline(40,13+i+i);
		print((order+i)->name);
		gotoline(61,13+i+i);
		print("Rs.");
		gotoline(64,13+i+i);
		printn((order+i)->price);
		gotoline(75,13+i+i);
		print("Rs.");
		gotoline(78,13+i+i);
		printn((order+i)->price*(order+i)->quantity);
		total+=(order+i)->price*(order+i)->quantity;
	}
	gotoline(75,(13+2*items));
	print("Rs.");
	gotoline(78,(13+2*items));
	printn(total);
	gotoline(75,(14+2*items));
	print("Rs.");
	gotoline(78,(14+2*items));
	saved=total*discount;
	printn(saved);
	gotoline(75,(16+2*items));
	print("Rs.");
	gotoline(78,(16+2*items));
	printn(total-saved);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
	gotoline(32,(22+2*items));
	print("\n");
}

void print_layout(int items){
	int loop,i;
	time_t t;
	time(&t);
	loop=21+items*2;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	for(i=0;i<loop;i++){
		gotoline(31,3+i);
		printf("                                                      ");
		printf("\n");
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	gotoline(32,4);
	printf("================== BILLING INVOICE =================");
	gotoline(51,5);
	printf("ABC Resturant");
	gotoline(32,7);
	printf("Customer name:");
	gotoline(32,8);
	printf("Phone number:");
	gotoline(32,11);
	printf("Qty\tItem\t\t     Price\t   Amount");
	gotoline(32,(12+2*items));
	printf("----------------------------------------------------");
	gotoline(68,(13+2*items));
	printf("Total: ");
	gotoline(65,(14+2*items));
	printf("discount: ");
	gotoline(74,(15+2*items));
	printf("---------");
	gotoline(59,(16+2*items));
	printf("Amount payable: ");
	gotoline(74,(17+2*items));
	printf("---------");
	gotoline(32,(19+2*items));
	printf("%s", ctime(&t));
	gotoline(32,(20+2*items));
	printf("====================================================");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
	Sleep(100);
}

void printn(int num){
	char output[10];
	sprintf(output, "%d", num);
	int j=0;
	while(output[j]!='\0'){
		Sleep(80);
		printf("%c", output[j++]);	
	}
}

void print(char output[]){
	int j=0;
	while(output[j]!='\0'){
		Sleep(80);	
		printf("%c", output[j++]);
	}
}

void give_voucher(int items){
	char code[6];
	srand(time(NULL));
	if(strcmp(mode,"YOUR")==0){
		code[0]=(char)(rand()%4)+69;
		code[1]=(char)(rand()%4)+69;
		code[2]=(char)(rand()%10)+48;
		code[3]=(char)(rand()%10)+48;
		code[4]=(char)(rand()%10)+48;
		code[5]='\0';
		FILE *fp;
		fp= fopen("vouchers.txt", "a");
		fprintf(fp,"%s\n", code);
		fclose(fp);
		gotoline(38,(21+2*items));
		print("**Use voucher \"");
		print(code);
		print("\" for discount next**");
		gotoline(48,(22+2*items));
		print("**time you order**");
		return;
	}
	else{
		gotoline(38,(21+2*items));
		print("**Order through an account next time**");
		gotoline(43,(22+2*items));
		print("**to get discount vouchers**");
	}
}

void loading(){
	int i; int j;
	system("cls");
	print_header();
	gotoline(51,5);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 249);
	printf("PRINTING BILL ");
	for(i=0;i<4;i++){
		gotoline(64,5);
		for(j=0; j<4; j++){
			printf(".");
			Sleep(250);
		}
		gotoline(64,5);
		printf("        ");
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
}
