#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//Citirea fiecarei linii
char** citire ( char **vector, int *n )
{
	int i = 0;
	do
	{
		//aloc memorie unui nou sir
		vector[i] = (char *) malloc ( 51 * sizeof ( char ) );
		scanf ( "%s", vector[i] ); //citesc un nou sir
		i++;
		//daca numarul de elemente depaseste dimensiunea vectorului de pointer,
		//aloc mai multa memorie
		if ( i % 10 == 0 )
			vector = (char **) realloc ( vector, ( i / 10 + 1 ) * 10 * sizeof ( char * ) );
	}
	//citesc elemente pana la intalnirea cuvantului "END"
	while ( strcmp ( vector[i - 1], "END" ) != 0 );
	*n = i;
	//Functia returneaza toate elementele citite
	return vector;
}

//Functie de verificare daca tipul unui termen este numar
int is_number ( char *termen )
{
	int i;
	//Verific daca primul caracter al sirului este o cifra sau '-'
	if ( termen[0] == 45 || isdigit (termen[0]) )
	{
		if ( strlen ( termen ) > 1 )
		{
			//verific daca restul caracterelor sunt cifre
			for ( i = 1; i < strlen ( termen ); i++ )
				if ( !isdigit ( termen[i] ) )
					//daca un caracter nu este cifra returnez 0
					return 0;
		}
		else
			if ( termen[0] == 45 )	
				return 0;
	}
	else 
		return 0;
	//daca toate caracterele sunt cifre, exceptie facand primul care poate fi '-' 
	//returnez valoarea 1
	return 1;
}

//Verificarea tipului unui termen si afisarea numarului din fiecare tip
void afisare_tip ( char **s, int n )
{
	//initializez contoarele care vor numara tipul fiecarui sir
	int i, numar = 0, caracter = 0, cuvant = 0;
	for ( i = 0; i < n -2 ; i++ )
		//testez daca este numar
		if ( is_number ( s[i] ) )
			//daca este numar incrementez variabila numar
			numar++;
		else
			//daca nu este numar verific daca este caracter 
			//daca sirul contine un singur element atunci este caracter
			if ( strlen ( s[i] ) == 1 )
				caracter++;
			else
				//daca nu este nici numar si nici caracter atunci este cuvant
				cuvant++;
	//afisez numarul de cuvinte, de caractere si de numere
	printf ( "%d %d %d\n", cuvant, caracter, numar );
}

//Verific daca un cuvant contine cifre
int cifre_cuvant ( char *cuvant )
{
	char cifra;
	//variabila de tip char parcurge codurile ASCII ale cifrelor
	for ( cifra = 48; cifra <= 57; cifra++ )
	{
		//verific daca in cuvant se afla cifra curenta
		if ( strchr ( cuvant, cifra ) )
			return 1;  //daca s-a gasit cel putin o cifra
	}
	return 0; //daca nu s-a gasit nicio cifra
}

//Inversarea unui sir de caractere
char* reverse ( char* cuvant )
{
	int inceput, sfarsit;
	char aux;
	//Parcurg sirul atat de la incepu cat si de sfarsit in acelasi timp
	for ( inceput = 0, sfarsit = ( strlen ( cuvant ) - 1 ); inceput < sfarsit; inceput++, sfarsit-- )
	{
		//inversez caracterele
		aux = cuvant[inceput];
		cuvant[inceput] = cuvant[sfarsit];
		cuvant[sfarsit] = aux;
	}
	return cuvant;
}

//Codificarea cuvintelor
char* codificare_cuvant ( char *cuvant )
{
	int l, d, exit = 0;
	l = strlen ( cuvant );
	//Calculez cel mai mare divizor al numarului de elemente din sir
	for ( d = l / 2; ( d >= 1 ) && ( exit == 0 ); d-- )
	{
		if ( l % d == 0 )
			exit = 1;
	}
	d++;
	//imi declar un pointer de tip char in care voi retine cuvantul codificat
	char* cuvant_codificat;
	//aloc memorie pointerului
	cuvant_codificat = (char *) malloc ( ( l + 1 ) * sizeof ( char ) );
	//verific daca cuvantul pe care trebuie sa-l codific contine cifre
	if ( cifre_cuvant ( cuvant ) )
	{
		//daca contine cifre, folosesc regula de codificare pentru cuvinte ce contin cifre
		strcpy ( cuvant_codificat, reverse ( cuvant + d ) );
		strncat ( cuvant_codificat, cuvant, d );
	}
	else
	{
		//daca nu contine cifre, folosesc regula de codificare pentru cuvinte ce nu contin cifre
		strcpy ( cuvant_codificat, cuvant + d );
		strncat ( cuvant_codificat, cuvant, d );
	}
	//returnez cuvantul codificat
	return cuvant_codificat;
}

//Codificarea caracterelor
char* codificare_caracter ( char *caracter, char* text_codificat )
{
	//imi initializez un vector de ce va retine frecventa de aparitie 
	//a fiecarui caracter din sir
	int *frecventa = (int *) calloc ( 96, sizeof ( int ) ), i, min, max;
	char caracter2 = caracter[0];
	for ( i = 0; i < strlen ( text_codificat ); i++ )
		frecventa[ (int)text_codificat[i] - 32 ]++;
	//initializez un minim si un max cu primul caracter din sir
	min = max = frecventa[ (int)text_codificat[0] - 32 ];
	char c_ap_max = text_codificat[0], c_ap_min = text_codificat[0];
	//calculez minimul si maximul
	for ( i = 1; i < strlen ( text_codificat ); i++ )
	{
		if ( min > frecventa[ (int)text_codificat[i] - 32 ] )
		{
			min = frecventa[ (int)text_codificat[i] - 32 ];
			c_ap_min = text_codificat[i];
		}
		if ( max < frecventa[ (int)text_codificat[i] - 32 ] )
		{
			max = frecventa[ (int)text_codificat[i] - 32 ];
			c_ap_max = text_codificat[i];
		}
	}
	//codific caracterul dupa regula specificata
	char *caracter_codificat = (char *) malloc ( 4 * sizeof ( char ) );
	caracter_codificat[0] = c_ap_max;
	caracter_codificat[1] = caracter2;
	caracter_codificat[2] = c_ap_min;
	caracter_codificat[3] = '\0';
	//eliberez memoria alocata vectorului de frecventa
	free ( frecventa );
	//returnez caracterul codificat
	return caracter_codificat;
}

//Codificarea numerelor
char* codificare_numar ( char* numar )
{
	int i;
	//verific daca numarul este negativ
	if ( numar[0] == 45 )
	{
		//numarul este negativ
		//elimin caracterul '-'
		char* aux = ( char* ) malloc ( ( strlen ( numar ) + 1 ) * sizeof ( char ) );
		strcpy ( aux, numar );
		strcpy ( numar, aux + 1 );
		//imi initializez un minim cu numarul curent
		//in minim calculez cel mai mic numar obtinut prin rotatii ciclice
		char* minim = (char *) malloc ( ( strlen ( numar ) + 1 ) * sizeof ( char ) );
		strcpy ( minim, numar );
		char *c = (char *) malloc ( 2 * sizeof (char) );
		c[1] = '\0';
		for ( i = 1; i < strlen ( numar ); i++ )
		{
			//creez un nou numar printr-o rotatie ciclica
			c[0] = numar[0];
			strcpy ( aux, numar );
			strcpy ( numar, aux + 1 );
			strcat ( numar, c );
			//daca noul numar este cel mai mic de pana acum il salvez
			if ( strcmp ( minim, numar ) > 0 )
				strcpy ( minim, numar );
		}
		//eliberez zona de memorie
		free ( aux );
		free (c);
		//returnez cel mai mic numar obtinut prin rotatii ciclice
		return minim;
	}
	else
	{
		//numarul este pozitiv
		//imi initializez un maxim cu numarul curent
		//in maxim calculez cel mai mare numar obtinut prin rotatii ciclice
		char* maxim = (char *) malloc ( ( strlen ( numar ) + 1 ) * sizeof ( char ) );
		char* aux = ( char* ) malloc ( ( strlen ( numar ) + 1 ) * sizeof ( char ) );
		strcpy ( maxim, numar );
		char *c = (char *) malloc ( 2 * sizeof (char) );
		c[1] = '\0';
		for ( i = 1; i < strlen ( numar ); i++ )
		{
			//creez un nou numar printr-o rotatie ciclica
			c[0] = numar[0];
			strcpy ( aux, numar );
			strcpy ( numar, aux + 1 );
			strcat ( numar, c );
			//daca noul numar este cel mai mare de pana acum il salvez
			if ( strcmp ( maxim, numar ) < 0 )
				strcpy ( maxim, numar );
		}
		//eliberez zona de memorie
		free (c);
		free ( aux );
		//returnez cel mai mare numar obtinut prin rotatii ciclice
		return maxim;
	}
}

//Codificarea textului
char* codificare ( char** text, int n )
{
	int i, dimensiune = 50;
	char* text_codificat = ( char* ) malloc ( dimensiune * sizeof ( char ) );
	//parcurg fiecare sir pe care trebuie sa-l codific
	strcpy ( text_codificat, "\0" );
	for ( i = 0; i < n - 2; i++ )
	{
		//verific tipul sirului
		if ( is_number ( text[i] ) )
		{
			//sirul este numar
			//initialize un pointer cu numarul codificat
			char* numar_codificat = codificare_numar ( text[i] );
			//daca nu exista suficienta memorie sa adaug numarul codificat la sir 
			//aloc mai multa
			if ( strlen ( text_codificat ) + strlen ( numar_codificat ) + 1 > dimensiune )
			{
				dimensiune += 50;
				text_codificat = ( char* ) realloc ( text_codificat, dimensiune * sizeof ( char ) );
			}
			//adaug cuvantul codifcat la sirul obtinut pana acum
			strcat ( text_codificat, numar_codificat );
			free ( numar_codificat );
		}
		else
			if ( strlen ( text[i] ) == 1 )
			{
				//sirul este caracter
				//daca nu exista suficienta memorie sa adaug caracterul codificat la sir 
				//aloc mai multa
				if ( strlen ( text_codificat ) + 5 > dimensiune )
				{
					dimensiune += 50;
					text_codificat = ( char* ) realloc ( text_codificat, dimensiune * sizeof ( char ) );
				}
				if ( strlen( text_codificat ) != 0 )
				{
					//codific caracterul si-l adaug la textul codificat
					char* caracter_codificat = codificare_caracter ( text[i], text_codificat );
					strcat ( text_codificat, caracter_codificat );
					free ( caracter_codificat );
				}
				else
					//textul codificat de pana acum este gol, pur si simplu adaug caracterul
					strcpy ( text_codificat, text[i] );
			}
			else
			{
				//sirul este cuvant
				//codific cuvantul
				char* cuvant_codificat = codificare_cuvant ( text[i] );
				//daca nu exista suficienta memorie sa adaug cuvantul codificat la sir 
				//aloc mai multa
				if ( strlen ( text_codificat ) + strlen ( cuvant_codificat ) + 1 > dimensiune )
				{
					dimensiune += 50;
					text_codificat = ( char* ) realloc ( text_codificat, dimensiune * sizeof ( char ) );
				}
				//adaug cuvatul codificat la textul codificat
				strcat ( text_codificat, cuvant_codificat );
				free ( cuvant_codificat );
			}
	}
	//returnez textul codificat
	return text_codificat;
}

//Definirea structurii cerute
typedef struct
{
	char* componenta;
	double complexitate;
}complex_string;

//Conversie din string in int
int string_to_int ( char* string )
{
	int numar = 0, i;
	for ( i = 0; i < strlen ( string ); i++ )
		numar = numar * 10 + ( ( int )string[i] - 48 );
	return numar;
}

//calculez complexitatea unui sir
double complexitate ( char* sir )
{
	int i;
	double complexitate_sir, s = 0;
	for ( i = 0; i < strlen ( sir ); i++ )
		s = s + (int)sir[i];
	complexitate_sir = s / strlen ( sir );
	return complexitate_sir;
}

//Sortarea vectorului 
complex_string* sortare ( complex_string* vect_comp, int n )
{
	int sw = 0, i;
	complex_string aux;
	do
	{
		sw = 0;
		for ( i = 0; i < n - 1; i++ )
		{
			if ( vect_comp[i].complexitate < vect_comp[ i + 1 ].complexitate )
			{
				aux = vect_comp[i];
				vect_comp[i] = vect_comp[i + 1];
				vect_comp[i + 1] = aux;
				sw = 1;
			}
			else
				if ( vect_comp[i].complexitate == vect_comp[ i + 1 ].complexitate )
					if ( strcmp ( vect_comp[i].componenta, vect_comp[i + 1].componenta ) > 0 )
					{
						aux = vect_comp[i];
						vect_comp[i] = vect_comp[i + 1];
						vect_comp[i + 1] = aux;
						sw = 1;
					}
		}
	}
	while ( sw == 1 );
	return vect_comp;
}

//Impartirea textului codificat pe componente
complex_string* impartire_comp ( char* text, int comp, long *dim_text_cod_re )
{
	long dim_comp, zona = 0, i;
	//Setez dimensiunea unei componente
	dim_comp = strlen ( text ) / comp;
	//declar un vector de componente de tipul struct complex_string
	complex_string* vect_comp;
	vect_comp = ( complex_string* ) malloc ( ( comp + 2) * sizeof ( complex_string ) );
	for ( i = 0; i < comp; i++ )
	{
		if ( i == comp - 1 )
			//cand ajung la ultima componenta, adaug tot ceea ce mai ramane
			dim_comp = strlen ( text + zona );
		vect_comp[i].componenta = ( char* ) malloc ( ( dim_comp + 1 ) * sizeof ( char ) );
		//initializez sirul cu NULL
		strcpy ( vect_comp[i].componenta, "\0" );
		//creez o componenta
		strncat ( vect_comp[i].componenta, text + zona, dim_comp );
		zona += dim_comp;
		//calculez si complexitatea componentei
		vect_comp[i].complexitate = complexitate ( vect_comp[i].componenta );
		*dim_text_cod_re += dim_comp;
	}
	//returnez vectorul ce contine toate componentele, precum si complexitatile acestora
	return vect_comp;
}

//Rearanjarea mesajului
char* rearanjare ( complex_string* vect_comp_sort, int comp, long dim_text_cod_re )
{
	int i;
	//declar un pointer, ii aloc memorie si-l initializez cu NULL
	char* text_codificat_rearanjat = ( char* ) malloc ( ( dim_text_cod_re + 1 ) * sizeof ( char ) );
	strcpy ( text_codificat_rearanjat, "\0" );
	//creez textul codificat prin aranjarea componentelor dupa regula specificata
	for ( i = 0; i < comp / 2; i++ )
	{
		strcat ( text_codificat_rearanjat, vect_comp_sort[i].componenta );
		strcat ( text_codificat_rearanjat, vect_comp_sort[ comp - i - 1 ].componenta );
	}
	if ( comp % 2 != 0 )
		//daca numarul de componente este impar, va ramane o componenta pe care o adaug aici
		strcat ( text_codificat_rearanjat, vect_comp_sort[ comp / 2 ].componenta );
	 //returneaza textul codificat final
	return text_codificat_rearanjat;
}

int main()
{
	char** text;
	int n = 0, i;
	//TASK 1
	//Citirea sirurilor
	//Initial aloc unui vector de pointeri memorie 10
	text = (char **) malloc( 10 * sizeof( char * ) );
	//Realizarea citirii
	text = citire( text, &n );
	//Afisarea fiecarui tip de termen
	afisare_tip ( text, n );

	//TASK 2
	//Codific fiecare element si-l adaug la text_codificat
	char *text_codificat = codificare ( text, n );
	//Afisez textul codificat conform taskului 2
	printf( "%s\n", text_codificat );

	//TASK 3
	//Extrag numarul de componente n, care se afla inaintea lui "END"
	int comp = string_to_int ( text[n-2] );
	//dim_text_cod_re va retine dimensiunea testului codificat rearanjat
	long dim_text_cod_re = 0;
	//Ipart textul pe componente
	complex_string *vect_comp = impartire_comp ( text_codificat, comp, &dim_text_cod_re );
	//Sortez componentele
	complex_string* vect_comp_sort = sortare ( vect_comp, comp );
	//Rearanjez textul
	char* text_codificat_rearanjat = rearanjare ( vect_comp_sort, comp, dim_text_cod_re );
	//Afisez textul codificat rearanjat
	printf("%s\n", text_codificat_rearanjat );
	
	//Eliberarea memoriei
	free ( text_codificat );
	for ( i = 0; i < comp; i++ )
		free ( vect_comp_sort[i].componenta );
	free ( vect_comp_sort );
	free ( text_codificat_rearanjat );
	for ( i = 0; i < n; i++ )
		free ( text[i] );
	free ( text );
	return 0;
}