#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <conio.h>
#include <fstream>
#include <string>
#include <ctype.h>

using namespace std;

/////////Something something function list///////
int Pariu1();
int Pariu2();
int Randomizer(int low, int high);
int CardValue(int card);
int getTopCard(int deck[]);
int GetBani1();
int GetBani2();
int getHandValue(const int hand[]);
bool IncaUnMeci(char&);
bool is_digits(const std::string &str);
bool userWantsToDraw(char&);
void InitializarePachet(int deck[]);
void dumpDeck(int deck[], int size);
void amestecare(int deck[], int size);
void ClearScreen();
void ShowCard(int card);
void menu();
void showMenu();
void showCards(const int cards[], int numCards, bool hideFirstCard);
void whoWins(const int pHand[], const int dHand[]);
void checkBust(const int pHand[], const int dHand[], char Play);
void blackJack(const int pHand[], const int dHand[], char Play);
void naturalBlackJack(const int pHand[], const int dHand[], char Play);
void playOneHand();
void Update1();
void UpdateMoney1();
void UpdateMoneyFile();
void UpdateMoneyFile2();
void Update2();
void UpdateMoney2();
void scoreBoard(const int pHand[], const int dHand[]);
void checkSoftOrHard(int pHand[]);
void softOrHardAI(int dHand[], int pHand[]);
void NivelDificult();
void showRules();
void addToHand(int hand[], int cardToAdd);
void hitUntilStand(int dHand[], int deck[], int pHand[]);
std::string GetNume();


int topCard = 0;
float scor = 1.00;
int level;
int Player1Bani;
int Player2Bani;
int rezultat=1;
int pariu;

int main()
{       showMenu();
        menu();
		return 0;
	}



/* ==================================================
Name: showMenu

================================================== */
void showMenu()
{
	cout << "//////////////////////////////////////////////////////////" << endl;
	cout << "////              Meniu BlackJack                    /////" << endl;
    cout<<  "////                                                 /////"<<endl;
    cout<<"////           1. Jucator vs Calculator              /////"<<endl;
    cout<<"////           2. Update Nume/Bani                   /////"<<endl;
    cout<<"////           3. Exit/Inchidere                     /////"<<endl;
    cout<<"////               Alege(1/2/3):";
}
/* ==================================================
Name: Menu

================================================== */
void menu()
{
		char a;
		string upData;
		cin>>a;
		if(a == '1')
            {
                showRules();
                NivelDificult();
                playOneHand();
            }
		else if(a == '2'){
                cout<<endl;
                cout<<"Ce doriti sa actualizati?"<<endl;
                cout<<"Nume sau bani? (1 pentru nume/2 pentru bani) :";
                cin>>upData;
                cout<<endl;
                if(upData[0]=='1')
                    {Update1();
                    cout<<endl;
                    cout<<"Modificarile au fost efectuate"<<endl;
                    showMenu();
                    menu();}
                else if(upData[0]=='2')
                    {UpdateMoney1();
                    cout<<endl;
                    cout<<"Modificarile au fost efectuate"<<endl;
                    showMenu();
                    menu();}
                else{
                    cout<<"Deoarece ati gresit va voi intoarce la meniu"<<endl;
                    showMenu();
                    menu();
                }
		}
		else if(a == '3')
                {ClearScreen();
                cout<<"/////////////////////////////////////////////////////////////////////////////"<<endl;
                cout<<"///////////////////           La revedere!              /////////////////////"<<endl;
                cout<<"/////////////////////////////////////////////////////////////////////////////"<<endl;
                exit(0);
                }

		else
		{
			cout<<endl;
			cout<<"////////          Alegere gresita                    /////"<<endl;
			cout<<endl;
			showMenu();
			menu();
		}

}
/* ==================================================
Name: Update nume

================================================== */
void Update1()
{
    std::ofstream out("Player1Nume.txt");
    string a;
    cout<<"Numele dumneavoastra(fara spatii)=";
    cin>>a;
    out << a;
    out.close();
}
void Update2()
{
    std::ofstream out("Player2Nume.txt");
    string a;
    cout<<"Numele=";
    cin>>a;
    out << a;
    out.close();

}
/* ==================================================
Name: Update bani   >cica doar plebeii baga comentarii
================================================== */
void UpdateMoney1()
{
ofstream out("Player1Money.txt");
string bani;
cout<<"Suma de bani=";
cin>>bani;
if(bani[0]=='-'){
    cout<<"Nu poti adauga o suma negativa"<<endl;
    out.close();
    UpdateMoney1();
           }
if(is_digits(bani)==0){
    cout<<"Nu poti adauga caractere "<<endl;
    out.close();
    UpdateMoney1();
        }

out<< bani;
out.close();
}


void UpdateMoney2()
{
ofstream out("Player2Money.txt");
int bani;
cout<<"Suma de bani=";
cin>>bani;
if(bani<=0){
    cout<<"Nu poti adauga o suma negativa"<<endl;
    out.close();
    UpdateMoney2();
}
out<< bani;
out.close();

}

/* ==================================================
Name: Update foldere
================================================== */
void UpdateMoneyFile(){
ofstream out("Player1Money.txt");
out.close();
ofstream out2("Player1Money.txt");
int x;
x=Player1Bani;
out2<< x;
out2.close();
}

void UpdateMoneyFile2(){
ofstream out("Player2Money.txt");
out.close();
ofstream out2("Player2Money.txt");
int x;
x=Player1Bani;
out2<< x;
out2.close();
}


/* ==================================================
Name: Sistem Pariuri  .dat_""""""system"""""
================================================== */
int GetBani1()
{ifstream fin("Player1Money.txt");
int x;
fin>>x;
return x;
}
int GetBani2()
{ifstream fin("Player2Money.txt");
int x;
fin>>x;
return x;
}

int Pariu1()
{
cout<<"Introduceti suma pe care doriti sa o pariati:";
int x,money;
money=GetBani1();
cin>>x;
if(x<=0||x>money){
    cout<<"Nu puteti paria aceeasta suma"<<endl;
    Pariu1();
}
return x;
}

int Pariu2()
{
cout<<"Introduceti suma pe care doriti sa o pariati:";
int y,money;
money=GetBani2();
cin>>y;
if(y<=0||y>money){
    cout<<"Nu puteti paria aceeasta suma"<<endl;
    Pariu2();
}
return y;
}

/* ==================================================
Name: #CataGraficaTata

================================================== */
void showRules()
{
	//Display rules and information in a visually pleasing graphic.
	cout << "//////////////////////////////////////////////////////////" << endl;
	cout << "////       Regulie jocului Blackjack/21              /////" << endl;
	cout << "////  _____________________________________________  /////" << endl;
	cout << "//// |                                             | /////" << endl;
	cout << "//// | o As-ul poate lua valoarea 1 sau 11.        | /////" << endl;
	cout << "//// | o Cartile J,Q,K primesc toate valoarea      | /////" << endl;
	cout << "//// |  egala cu cartea 10.                        | /////" << endl;
	cout << "//// |                                             | /////" << endl;
	cout << "//// | Scor -                                      | /////" << endl;
	cout << "//// | Scorul este bazat pe valoarea castigului sau| /////" << endl;
	cout << "//// | al unei infrangeri.                         | /////" << endl;
	cout << "//// | o Punctajul tau este mai mare ca al casei.  | /////" << endl;
	cout << "//// |   Scorul creste cu 1.                       | /////" << endl;
	cout << "//// |                                             | /////" << endl;
	cout << "//// | o Punctajul Dealer-ului este mai mare.      | /////" << endl;
	cout << "//// |   Scorul scade cu 1.                        | /////" << endl;
	cout << "//// |                                             | /////" << endl;
	cout << "//// | o Blackjack - 21 de puncte.                 | /////" << endl;
	cout << "//// |   Scorul creste cu 1.5.                     | /////" << endl;
	cout << "//// |                                             | /////" << endl;
	cout << "//// | o Blackjack Natural -                       | /////" << endl;
	cout << "//// |   21 de puncte dupa prima mana.             | /////" << endl;
	cout << "//// |   Scorul creste cu 1.5.                     | /////" << endl;
	cout << "//// | o Egalitate -                               | /////" << endl;
	cout << "//// |   Scorul nu creste.                         | /////" << endl;
	cout << "//// |   Pierzi banii din pariu.                   | /////" << endl;
	cout << "//// |                                             | /////" << endl;
	cout << "//// |                                             | /////" << endl;
	cout << "//// |                                             | /////" << endl;
	cout << "//// |_____________________________________________| /////" << endl;
	cout << "//////////////////////////////////////////////////////////" << endl;

}

/* ==================================================
Name: Nivel Dificultate

================================================== */
void NivelDificult()
{

	cout << "\n";
	cout << "Nivelul dificultatii: Incepator (1), Expert (2). ";
	cin >> level;
	cout << "\n";


	if(level != 1)
	{
		if(level != 2)
		{

			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');


			cout << "Te rog introdu unul din urmatoarele numerele:1 sau 2" << endl;
			NivelDificult();
		}
	}
}
/* ==================================================
Name: CS
Counter strike???
================================================== */

  void ClearScreen()
    {
    int n;
    for (n = 0; n < 100; n++)
      printf( "\n\n\n\n\n\n\n\n\n\n" );
    }
 /* ==================================================
Name: GetNume (direct3DinFisier)
================================================== */

std::string GetNume()
{ifstream fin("Player1Nume.txt");
string name;
int i;
for(i=0;i<=20;i++){
    fin>>name;
}
return name;
}

/* ==================================================
Name: playOneHand (Toata frumusetea jocului)

================================================== */
void playOneHand()
{
	char Play = 'N';
	Player1Bani=GetBani1();
	if(Player1Bani<=0){
        ClearScreen();
        cout<<"Nu aveti suma necesara pentru a paria."<<endl;
        showMenu();
        menu();
	}
	cout<<"Aveti in cont suma de:"<<" " <<Player1Bani<<endl;
	pariu=Pariu1();
	do
	{
		char Draw = 'H';
		int deck[52];
		InitializarePachet(deck);
		amestecare(deck, 51);
		int pHand[10] = {0};
		int dHand[10] = {0};
		addToHand(pHand, getTopCard(deck));
		addToHand(dHand, getTopCard(deck));
		addToHand(pHand, getTopCard(deck));
		addToHand(dHand, getTopCard(deck));

		cout << "//////////////////////////////////////////////////////////" << endl;
		cout << "\n" << endl;
		cout << "Dealer-ul a amestecat pachetul de carti si a dat cate doua carti fiecarui jucator. ";
		cout << "\n" << endl;

		naturalBlackJack(pHand, dHand, 'y');
		blackJack(pHand, dHand, 'Y');
		cout << "Cartile lui"<<" "<<GetNume()<< endl;
		showCards(pHand, 10, false);
		cout << "\n\nCartile Dealer-ului:" << endl;
		showCards(dHand, 10, true);
		checkSoftOrHard(pHand);

		while (userWantsToDraw(Draw))
		{
            addToHand(pHand, getTopCard(deck));
			cout << "Dealer-ul ti-a dat alta carte:\n" << endl;
			cout << "Cartile tale" << endl;
			showCards(pHand, 10, false);
			checkSoftOrHard(pHand);
			checkBust(pHand, dHand, 'y');
			blackJack(pHand, dHand, 'Y');
		}

		hitUntilStand(dHand, deck, pHand);
		cout << endl;
		checkBust(pHand, dHand, 'Y');
		blackJack(pHand, dHand, 'Y');
		whoWins(pHand, dHand);
		cout << endl;
		cout << "Scor: " << scor << endl;
		if(rezultat==1)
            {Player1Bani=Player1Bani+pariu;
            cout<<"Ai in cont:"<<" "<<Player1Bani<<endl;
            UpdateMoneyFile();
            }
        else
            {Player1Bani=Player1Bani-pariu;
            cout<<"Ai in cont:"<<" "<<Player1Bani<<endl;
            UpdateMoneyFile();
            }
	}
	while (IncaUnMeci(Play));
}

/* ==================================================
Name: InitializarePachetCarti

================================================== */
void InitializarePachet(int deck[])
{
	int Rank = 101;
	int i = 0;

	for (i = 0 ; i<=13; i++)
	{
		deck[i] = Rank++;
	}

	for (i = 13 ; i<=26; i++)
	{
		deck[i] = Rank++ + 100 - 14;
	}

	for (i = 26 ; i<=39; i++)
	{
		deck[i] = Rank++ + 200 - 28;
	}

	for (i = 39 ; i<=51; i++)
	{
		deck[i] = Rank++ + 300 - 42;
	}
}

/* ==================================================
Name: amestecarePachet

================================================== */
void amestecare(int deck[], int size)
{
	for(int i = 0; i < 500; i++)
	{
		int T1 = 0;
		int R1 = Randomizer(0, size);
		int R2 = Randomizer(0, size);

		T1	= deck[R1];
		deck[R1] = deck[R2];
		deck[R2] = T1;
	}
}

/* ==================================================
Name: ShowCard(Afisare carti)

================================================== */
void ShowCard(int card)
{
	if(card == 0)
	{
		cout << "";
	}
	else
	{
		switch(card % 100)
		{
			case 1:
				cout << "A";
				break;
			case 11:
				cout << "J";
				break;
			case 12:
				cout << "K";
				break;
			case 13:
				cout << "Q";
				break;
			case 14:
				cout << "A";
				break;

			default:
				cout << card % 100;
		}
	}

	if(card == 0)
	{
		cout << "";
	}
	else
	{
	   if((card >= 101) && (card <=114))
		{
			cout << static_cast<char>(3);
		}

		else if ((card >= 201) && (card <= 214))
		{
			cout << static_cast<char>(4);
		}

		else if ((card >= 301) && (card <= 314))
		{
			cout << static_cast<char>(5);
		}

		else if ((card >= 401) && (card <= 414))
		{
			cout << static_cast<char>(6);
		}
	}
}

/* ==================================================
Name: ShowCards(Afisare reala carti)

================================================== */
void showCards(const int deck[], int numCards, bool hideFirstCard)
{
	if(hideFirstCard)
	{
		cout << "** ";
	}

	else
	{
		ShowCard(deck[0]);
		cout << " ";
	}

	for(int i = 1; i < numCards; i++)
	{
		if(deck[i] != 0)
		{
			ShowCard(deck[i]);
			cout << " ";
		}

		else
		{
			cout << "";
		}
	}
}

/* ==================================================
Name: dumpDeck (>full of use)

================================================== */
void dumpDeck(int deck[], int size)
{
	for(int i = 0; i < size; i++)
	{
		cout << i + 1 << ".) " << deck[i] << endl;
	}
}

/* ==================================================
Name: Randomizer (genereaza numar >random)

================================================== */
int Randomizer(int low, int high) {
	static bool firstTime=true;
	int randNum;

	if (firstTime) {
		srand( static_cast<unsigned int>(time(NULL)) );
		firstTime=false;
	}

	randNum = rand() % (high-low+1) + low;

	return randNum;
}

/* ==================================================
Name: CardValue (valoarea carte----->Dificultate/Calcul puncte)

================================================== */
int CardValue(int card)
{
	int cardVal;

	switch(card % 100)
	{
		case 1:
			cardVal = 11;
			break;
		case 11:
		case 12:
		case 13:
			cardVal = 10;
			break;
		case 14:
			cardVal = 1;
			break;
		default:
		cardVal = (card % 100);
	}
	return cardVal;
}

/* ==================================================
Name: getTopCard

================================================== */
int getTopCard(int deck[])
{
    for(int i = 0; i < 51; i++)
    {
        if(deck[i] != 0)
        {
            topCard = deck[i];
            deck[i] = 0;
            return topCard;
        }
    }
}

/* ==================================================
Name: addToHand

================================================== */
void addToHand(int hand[], int cardToAdd)
{
	for(int i = 0; i < 9; i++)
	{
		if(hand[i] == 0)
		{
			hand[i] = cardToAdd;
			break;
		}
	}
}

/* ==================================================
Name: hitUntilStand (Limitare Dealer-momentan 17)

================================================== */
void hitUntilStand(int dHand[], int deck[], int pHand[])
{

	for(int i = 0; i < 9; i++)
	{
		if(getHandValue(dHand) < 17)
		{
			if(level == 1)
			{
					addToHand(dHand, getTopCard(deck));
			}
			else if( level == 2)
			{
				addToHand(dHand, getTopCard(deck));
				softOrHardAI(dHand, pHand);
			}
		}
		else
		{
			if(i == 0)
			{
				cout << "Dealer-ul loveste." << endl;
				break;
			}
			else if(i == 1)
			{
				cout << "Dealer-ul ia o carte si ramane" << endl;
				break;
			}
			else
			{
				cout << "Dealer-ul a luat " << i << " carti si ramane." << endl;
				break;
			}
		}

		if(level == 1);
		else if( level == 2)
		{
			softOrHardAI(dHand, pHand);
		}
	}
}

/* ==================================================
Name: getHandValue(Calcul pentru valoarea de puncte)

================================================== */
int getHandValue(const int hand[])
{
	int addCardValues = 0;

	for(int i = 0; i < 9; i++)
	{
		addCardValues = addCardValues + CardValue(hand[i]);
	}

	return addCardValues;
}

/* ==================================================
Name: IncaUnMeci

==================================================*/
bool IncaUnMeci(char& Joaca)
{

	cout << endl << "\nVrei sa joci alt meci? (Y/N) ";
	cin >> Joaca;
	cout << "\n" << endl;

	if(Joaca == 'y' || Joaca == 'Y')
	{
		playOneHand();
		return(true);
	}
	else
	{
	    ClearScreen();
		showMenu();
		menu();
	    return(false);
	}
}

/* ==================================================
Name: userWantsToDraw(To hit or not to hit, that's the "QuestChin")

==================================================*/
bool userWantsToDraw(char& Draw)
{

	cout << endl << "\n Vrei sa primesti o carte sau sa ramai?(H/S) ";
	cin >> Draw;
	cout << "\n";

	if(Draw == 'h' || Draw == 'H')
	{
			return(true);
	}
	else
	{
		return(false);
	}
}

/* ==================================================
Name: whoWins

================================================== */
void whoWins(const int pHand[], const int dHand[])
{
	int playerScore = getHandValue(pHand);
	int dealerScore = getHandValue(dHand);

	scoreBoard(pHand,  dHand);

	if(playerScore < 22 && playerScore > dealerScore || dealerScore > 21 && playerScore < 22)

	{
		cout << "\n";
		cout << "Ai Castigat!" << endl;
		scor++;
		rezultat=1;
	}
	else
	{

		if(playerScore == dealerScore)
		{
			cout << "\n";
			cout << "Puncte egale.Nu primesti bani si nici nu iti creste scorul" << endl;
		}


		else
		{
			cout << "\n";
			cout << "Ai pierdut" << endl;
			scor--;
			rezultat=0;
		}
	}
}

/* ==================================================
Name: check Bust(afisare trecerea peste limita punctajului)

================================================== */
void checkBust(const int pHand[], const int dHand[], char Play)
{
	int playerScore = getHandValue(pHand);
	int dealerScore = getHandValue(dHand);
	Player1Bani=GetBani1();


	if(playerScore > 21)
	{
		cout << "Ai trecut peste limita avand " << getHandValue(pHand) << " de puncte." << endl;
		cout << "\n" << endl;
		scor--;
		Player1Bani=Player1Bani-pariu;
		UpdateMoneyFile();
		cout << "Scor:" << scor << endl;
		IncaUnMeci(Play);
	}

	else if(dealerScore > 21)
	{
		scoreBoard(pHand,  dHand);
		cout << "\n" << endl;
		cout << "Dealer-ul a trecut peste limita de puncte!" << endl;
		cout << "\n" << endl;
		scor++;
        Player1Bani=Player1Bani+pariu;
		UpdateMoneyFile();
		cout << "Scor: " << scor << endl;
		IncaUnMeci(Play);
	}
}

/* ==================================================
Name: blackJack(Player+Dealer)

================================================== */
void blackJack(const int pHand[], const int dHand[], char Play)
{
	int playerScore = getHandValue(pHand);
	int dealerScore = getHandValue(dHand);
	Player1Bani=GetBani1();
	if((playerScore == 21) && (dealerScore != 21))
	{
		cout << "\n\n";
		scoreBoard(pHand,  dHand);
		cout << "\n";
		cout << "Blackjack! Ai castigat si ai primit bonus la scor." << endl;
		scor = scor + 1.5;
        Player1Bani=Player1Bani+pariu;
		UpdateMoneyFile();
		cout << "\n";
		cout << "Scor: " << scor << endl;
		IncaUnMeci(Play);
	}
	else if((playerScore == 21) && (dealerScore == 21))
	{
		scoreBoard(pHand,  dHand);
		cout << "\n";
		cout << "Atat Dealer-ul cat si dumneavoastra ati primit 21 de puncte.Scorul va creste insa nu si banii" << endl;
		scor++;
		cout << "\n";
		cout << "Scor " << scor << endl;
		IncaUnMeci(Play);
	}
}

/* ==================================================
Name: is_digits verificare (string = doar numere)
================================================== */
bool is_digits(const std::string &str)
{
    return str.find_first_not_of("0123456789") == std::string::npos;
}
/* ==================================================
Name: naturalBlackJack(====Bulan)

================================================== */
void naturalBlackJack(const int pHand[], const int dHand[], char Play)
{
	int playerScore = getHandValue(pHand);
	int dealerScore = getHandValue(dHand);
	Player1Bani=GetBani1();

	if((playerScore == 21) && (dealerScore != 21))
	{
		scoreBoard(pHand,  dHand);
		cout << "\n";
		cout << "Blackjack! Ai castigat si ai primit bonus la scor.";
		Player1Bani=Player1Bani+pariu;
        UpdateMoneyFile();
		scor = scor + 1.5;
		IncaUnMeci(Play);
	}
}

/* ==================================================
Name: scoreBoard(Afisare punctaj duh)

================================================== */
void scoreBoard(const int pHand[], const int dHand[])
{
 	cout << "Cartile lui"<<" "<<GetNume()<<" ";
	showCards(pHand, 10, false);
	cout << " ("<< getHandValue(pHand) << "pts)."<<endl;

	cout <<"V.S." << endl;

	cout << "Cartile Dealer-ului: ";
	showCards(dHand, 10, false);
	cout << " ("<< getHandValue(dHand) << "pts)."<<endl;
}

/* ==================================================
Name: checkSoftOrHard(Toata treaba cu As=1/11)

================================================== */
void checkSoftOrHard(int pHand[])
{
	for(int i=0; i<9; i++)
	{
		int checkAce = CardValue(pHand[i]);
		int softOrHard;

		if(checkAce == 1 || checkAce == 11)
		{
			cout << "\n";
			cout << "\nAti dori ca As-ul dumneavoastra sa primeasca valoarea 1 sau 11(1/11): ";
			cin >> softOrHard;

			if(softOrHard == 1)
			{
				if(checkAce == 11)
				pHand[i] = pHand[i] + 13;
			}

			else if(softOrHard == 11)
			{
				if(checkAce == 1)
				{
					pHand[i] = pHand[i] - 13;
				}
			}

			else if (softOrHard != 1 || softOrHard != 11)
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "\nVa rog inserati fie valoarea 1 fie 11:" << endl;
				checkSoftOrHard(pHand);
			}
		}
	}
}

/* ==================================================
Name: checkSoftOrHardAI

================================================== */
void softOrHardAI(int dHand[], int pHand[])
{
	for(int i=0; i<9; i++)
	{
		if(CardValue(dHand[i]) == 1 || CardValue(dHand[i]) == 11)
		{
			if(CardValue(dHand[i]) == 11)
			{
				if (getHandValue(dHand) - CardValue(dHand[i]) + 1 > getHandValue(pHand))
				{
					if (getHandValue(dHand) - CardValue(dHand[i]) + 1 < 22)
					{
						dHand[i] = dHand[i] + 13;
					}
				}

				else if (getHandValue(dHand) > 21)
				{
					dHand[i] = dHand[i] + 13;
				}
			}

			else
			{
				if (getHandValue(dHand) - CardValue(dHand[i]) + 11 > getHandValue(pHand))
				{
					if (getHandValue(dHand) - CardValue(dHand[i]) + 11 < 22)
					{
						dHand[i] = dHand[i] - 13;
					}
				}
			}
		}
	}
}


