#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct liste {
 	char kelime[20];
	int adet;
	struct liste *next;
};
typedef struct liste Liste;

void okuma(char current[]);
void kelimeAl(char metin[],Liste **headOfList);
void kontrol(char kelime[],Liste **headOfList);
void listeEkleme(char kelime[],int sayac,Liste **headOfList);
void listeBastirma(Liste* headOfList);
int arama(char kelime[],Liste* headOfList);
void basaEkleme(Liste* newWords,Liste **headOfList);
void sonaEkleme(Liste* newWords,Liste *currentList);
void arayaEkleme(Liste* newWords,Liste *currentList);

char metin[100];

int main(){
	Liste *headOfList = NULL;
	okuma(metin);
	/*	
	// metni ekrana bastýrma ---------------------
	int i ;
	while(metin[i] !='\0'){
		printf("%c",metin[i]);
		i++;
	}
	// metni ekrana bastýrma ---------------------
	*/
	kelimeAl(metin,&headOfList);
	listeBastirma(headOfList);
	return 0;
}

void okuma(char metin[]){
	FILE *readd = NULL;
	int i  = 0;
	int counter = 0;
	char kelime;
	if((readd = fopen("metin.txt","r")) != NULL){
		while(!feof(readd)){
			fscanf(readd,"%c",&kelime);
			if(kelime >='A' &&  kelime <= 'Z'){ // DOWN CASÝNG ÝSLEMÝ
				kelime = kelime +32;
			}
			metin[i] = kelime;
			i++;	
		}
		
	}else{
		printf("The file could not be raed!!\n");
		fclose(readd);
		exit(EXIT_FAILURE);
	}
	
	
}

void kelimeAl(char metin[],Liste **headOfList){
	int i = 0;
	int j = 0;
	char kelime[20];
	while(metin[i] != '\0'){
		if(metin[i+1] == ' '){
			kelime[j]=metin[i];
			kelime[j+1] = '\0';
			j = 0;
			kontrol(kelime,headOfList); // metinde yazýldýðý sýrada kelimeler okunur ve kontrol methoduna yollanýr. 
		}else{
			if(metin[i] != ' ' && metin[i+1] != '\0'){
				kelime[j] = metin[i];
				j++;	
			}
		}
		i++;
	}
}


void kontrol(char kelime[],Liste **headOfList){
	char geciciKelime[20];
	int i = 0;
	int j = 0;
	int sayac = 0;
	int counter = 0;
	while(metin[i] != '\0'){  
		if(metin[i+1] == ' '){
			geciciKelime[j]=metin[i];
			geciciKelime[j+1] = '\0';
			j = 0;
			if(strcmp(geciciKelime,kelime) == 0){ // metinde verilen sýrada kelimeler alýnýr ve parametre olarak yollananan kelimeye eþit olanlar kontrol edilir
				sayac++; // Metinde parametre olarak yollanan kelimeden kaçtane oldugunu sayacý arttýrarak görülür
			}
		}else{
			if(metin[i] != ' '){
				geciciKelime[j] = metin[i];
				j++;	
			}
		}
		i++;
	}
	if(arama(kelime,*headOfList) == 0){ // bagli listede eger o kelime eklenmemisse  
		listeEkleme(kelime,sayac,headOfList); // bagli listeye ekleme yapilir
	}
}

void listeEkleme(char kelime[],int sayac,Liste **headOfList){
	Liste *currentList = (*headOfList); // CURRENTLIST LISTENIN BASINI GOSTERIYOR
	Liste *newWords = (Liste*)malloc(sizeof(Liste)); // YENI DUGUM OLSTURULUR
	strcpy(newWords->kelime,kelime); // DUGUMUN KELIMESI PARAMETRE OLARAK GELEN KELIME EKLENIR
	newWords->adet = sayac; // DUGUMUN ADET SAYISI PARAMETRE OLARAK GELEN KELIMENIN TEKRAR SAYISI EKLENIR
	if(currentList == NULL){ // BAGLI LISTE BOSSA
			basaEkleme(newWords,headOfList);
    }else if (currentList -> next == NULL){ // BAGLI LISTEDE 1 ELEMAN VARSA 
		if(currentList -> adet > sayac){ // LÝSTEDEKÝ KELÝMENÝN TEKRAR SAYISI  EKLÝCEGÝMÝZDEN KELÝMENÝN TEKRAR SAYISINDAN FAZLAYSA
			sonaEkleme(newWords,currentList); // SONA EKLEME YAPILIR
		}else if(currentList -> adet < sayac){ // LÝSTEDEKÝ KELÝMENÝN TEKRAR SAYISI EKLICEGIMIZ KELÝMENÝN TEKRAR SAYISINDAN AZ ISE
			basaEkleme(newWords,headOfList); // BASA EKLEME YAPILIR
		}
	}else{ // BAGLI LÝSTEDE 1'DEN FAZLA ELEMAN VAR ÝSE
		while(currentList !=NULL){
			if(currentList->adet > sayac ){ // LÝSTEDEKÝ ÝLK ELEMANIN TEKRAR SAYISI EKLENILCEK KELIMENIN TEKRARINDAN FAZLA ISE
				if(currentList -> next != NULL && currentList -> next -> adet < sayac){ // LÝSTEDE 2 VE 2 DEN FAZLA ELEMAN  VAR VE 2.ELEMANIN TEKRAR SAYISI BÝZÝM EKLÝCEGÝMÝZ KELÝMENÝN TEKRAR SAYISINDAN AZ ÝSE
					arayaEkleme(newWords,currentList);  // ARAYA EKLEME YAPILIR
					break;
				}else if(currentList -> next != NULL && currentList -> next -> adet  ==  sayac){ // LÝSTEDE 2 VE 2 DEN FAZLA ELEMAN VAR VE 2.ELEAMANIN TEKRAR SAYISI BIZIM EKLICEGIMIZ KELIMENIN TEKRAR SAYISINA ESIT ISE
					while( currentList -> next != NULL && currentList -> next -> adet == sayac  ){// LISTEDE TEKRAR SAYILARI AYNI OLAN KELIMELERIN SONUNA KADAR GIDILIR
						currentList = currentList -> next;
					}
					// 6 5 5 5  LÝSTE OLDUGUNU DUSUNURSEK  CURRENT EN SONDAKI 5 I GOSTERIYOR OLUR (EKLENICEK ELEMAN 5)
					// 5 3 3 3 2 1 OLDUGUNU DUSUUNURSEK CURRENT BASTAN BAKILIRKEN EN SON OLAN 3 U GOSTERIR(EKLENICEK ELEMAN 3 )
					if(currentList -> next  == NULL){ // EGER SONDAKINI GOSTERIYORSA
						sonaEkleme(newWords,currentList); // SONA EKLEME YAPILIR
					}else{
						arayaEkleme(newWords,currentList); // ARAYA EKLEME YAPILIR
					}
					break;
					// 5 4  LISTE OLDUGUNU DUSUNURSEK CURRENT (EKLENICEK ELEMAN 4 OLDUGUNDA)
				}else if(currentList -> next == NULL){// CURRENT EN SON 4  GOSTERIP
					sonaEkleme(newWords,currentList); // SONA EKLEME YAPILIR
					break;
				}
			}else if (currentList -> adet  == sayac){ // LISTENIN BASINDAKI ELEMANIN TEKRAR SAYISI EKLENICEK KELIMENIN TEKRAR SAYISINA ESIT ISE
				while( currentList -> next != NULL && currentList -> next -> adet == sayac  ){ // LISTEDE TEKRAR SAYISI AYNI OLANIN SONUNA KADAR GIDILRI
					currentList = currentList -> next;
				}
				// 5 5 5 4  NULL  CURRENT  EN SON 4 DEN ONCEKI 5'I GOSTERIR(5 EKLENICEK)
				// 5 5 5  NULL   CURRENT EN SON KI 5 I GOSTERIR(5 EKLENICEK)
				if(currentList -> next  == NULL){// EGER CURRENTTEN SONRA NULL VAR ISTE
					sonaEkleme(newWords,currentList); // SONA EKLEME YAPILRI
				}else{
					arayaEkleme(newWords,currentList); // ARAYA EKLEME YAPILIR
				}
				break;
			}else{// LÝSTEDEKÝ ÝLK ELEMANIN TEKRAR SAYISI EKLENILCEK KELIMENIN TEKRARINDAN AZ ISE
				//  4 4 3 3 2 1 NULL  OLDUGUNDA LISTE( 5 EKLENICEK OLURSA)
				basaEkleme(newWords,headOfList); // BASA EKLEME YAPILIR
				break;
			}
			currentList = currentList->next;
			}
		}
}
	
void basaEkleme(Liste* newWords,Liste **headOfList){
	if((*headOfList) == NULL){ // LISTE BOS ISE
		newWords->next = NULL; 
		(*headOfList) = newWords;
	}else{
		newWords->next = (*headOfList); 
		(*headOfList)= newWords;
	}
}

void sonaEkleme(Liste* newWords,Liste *currentList){
	newWords->next = NULL;
	currentList -> next = newWords;
}

void arayaEkleme(Liste* newWords,Liste *currentList){
	newWords -> next = currentList -> next;
	currentList -> next= newWords;
}

int arama(char kelime[],Liste *headOfList){
	Liste *currentList = headOfList;// LISTENIN BASINI GOSTERIR
	while(currentList!= NULL && strcmp(currentList->kelime,kelime) != 0){// CURRENTLIST NULL GOSTERMEYENE KADAR VE AYNI KELIMEDEN BULMAYANA KADAR LISTEYI GEZER
		currentList = currentList->next;
	}
	if(currentList == NULL){ // EGERKI NULL GOSTERIYORSA EKLENICEK ELEMAN LISTEDE YOKTUR
		return 0; // 0 DEGERÝ DONDURULUR
	}else{
		return -1; // EGERKI NULL GOSTERMIYORSA EKLENICEK ELEMAN LISTEDE VARDIR  -1 DEGERI DONDURULUR
	}
}

void listeBastirma(Liste* headOfList){
	Liste* currentList = headOfList;
	int i;
	int counter = 1;
	//printf("\n");
	while(currentList !=NULL){
		printf("%d. ",counter);
		for(i = 0;i<strlen(currentList->kelime);i++){
		printf("%c",currentList->kelime[i]);
		}
		printf(":%d\n",currentList->adet);
		currentList = currentList -> next;
		counter++;
	}
}
