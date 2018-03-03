Explicatia algoritmului folosit
Timp alocat: 12 ore
Task 1 - citirea

Pentru citire am construit functia char** citire ( char **vector, int *n ).
Aceasta functie primeste ca prim argument un vector de pointeri in care se va 
face citirea. Fiecare element citit se retine in acest vector. Al doilea argument
reprezinta variabila in care se va retine numarul elementelor vectorului.
Functia citeste siruri pana la intalnirea sirului "END". Inainte de a citi
elementul i se aloca o anumita memorie ( 51 ). Daca numarul de elemente este
mai mare de cat memoria alocata vectorului  de pointeri, atunci se aloca mai
multa memorie vectorului de pointeri.

Functia "int is_number ( char *termen )" verifica daca un string dat ca
parametru este numar. Functia parcurge fiecare carater al stringului si verifica
daca acesta este cifra, exceptie facand primul argument care poate fi "-",
deoarece numarul poate fi si negativ.

Functia void afisare_tip ( char **s, int n ) afiseaza numarul cuvintelor, al
caracterelor si al numerelor din text. Functia ia fiecare element si verifica
daca este numar, caracter sau cuvant si incrementeaza variabila corespunzatoare.

Task 2 - codificarea

Codificarea cuvintelor
Functii folosite:
	int cifre_cuvant ( char *cuvant )
	char* reverse ( char* cuvant )
	char* codificare_cuvant ( char *cuvant )

Functia int cifre_cuvant ( char *cuvant ) verifica daca se afla cifre intr-un
cuvant. Se ia un contor i care parcurge toate caracterele cifre in format ASCII
si verifica daca se gaseste in cuvant.

Functia char* reverse ( char* cuvant ) returneaza inversul unui cuvant.
Se parcurge cuvantul caracter cu caracter de la stanga la dreapta si de la
dreapta la stanga in acelasi timp si se inverseaza caracterele.

Functia char* codificare_cuvant ( char *cuvant ) realizeaza codificarea
cuvintelor. 
	Calculeaza in d cel mai mare divizor al numarului de elemente al sirului.
Verifica daca cuvantul contine cifre. Daca contine se foloseste regula de
codificare pentru cuvinte ce contin cifre ( se iau primele d caractere si se pun
la sfarsit, restul caracterelo vor fi inversate ). Daca cuvantul nu contine
cifre se foloseste regula de codificare pentru cuvinte care nu contin cifre
( se iau primele d caractere si se pun la sfarsit, restul caracterelo ramanand
neschimbate ).

Codificarea caracterelor
Functii folosite:
	char* codificare_caracter ( char *caracter, char* text_codificat )

Functia char* codificare_caracter ( char *caracter, char* text_codificat ) 
codifica caracterul primit ca prim argument. Functia construieste un vector
care retine frecventa de aparitie al fiecarui caracter din sir. Apoi verifica
care caracter din sir are frecventa minima, respectiv maxima. Adauga primul
caracter care apare de cele mai multe ori inaintea caracterului care trebuie
codificat, iar primul element cu cel mai mic numar de aparitii din text se
adauga la sfarsit.

Codificarea numerelor
Functii folosite:
	char* codificare_numar ( char* numar )

Functia char* codificare_numar ( char* numar ) codifica numarul primit ca
argument. Verifica daca numarul este negativ sau pozitiv. Daca este negativ
il face pozitiv si calculeaza cel mai mic numar obtinut prin rotiri ciclice.
Daca este pozitiv, functia calculeaza cel mai mare numar obtinut prin rotiri
ciclice. Pentru a obtine un numar printr-o rotire ciclica se retine ultima cifra,
apoi restul cifrelor se copiaza intr-o variabila auxiliara, apoi se pune cifra
salvata la inceput.

Codificarea textului
Functii folosite:
	char* codificare ( char** text, int n )

Functia char* codificare ( char** text, int n ) codifica textul primit ca
argument urmand urmatorii pasii:
	-verifica tipul fiecarui termen ( cuvant, caracter, numar )
	-in functie de tipul elementului foloseste codificarea corespunzatoare
	-adauga termenul codificat la sirul in care se memoreaza textul codificat
Se apeleaza functia cu textul citit de la taskul 1.
Dupa ce se codifica textul, acesata se afiseaza.

Task 3 - rearanjarea
Se creeaza structura ceruta ( typedef struct complex_string )
Functii folosite:
	int string_to_int ( char* string )
	double complexitate ( char* sir )
	complex_string* sortare ( complex_string* vect_comp, int n )
	complex_string* impartire_comp ( char* text, int comp, long *dim_text_cod_re )
	char* rearanjare ( complex_string* vect_comp_sort, int comp, long dim_text_cod_re )
 
Fuctia int string_to_int ( char* string ) transforma un sir de cifre intr-un
numar. Se parcurge sirul caracter cu caracter si folosind codul ASCII se adauga
cifra la noul numar.

Functia double complexitate ( char* sir ) calculeaza complexitatea unui sir.
Se parcurge sirul caracter cu caracter si se face suma codurilor ASCII. Apoi
se imparte suma obtinuta la numarul de  caracatere.

Functia complex_string* sortare ( complex_string* vect_comp, int n ) sorteaza
un vector de forma complex string, folosind bubble sort, descrescator dupa
complexitate, iar daca complexitatile sunt egale se sorteaza lexicografic dupa
componente.

Functia complex_string* impartire_comp ( char* text, int comp, 
long *dim_text_cod_re ) imparte textul in "comp" componente. Calculeaza dimensiunea
unei componente ca fiind numarul caracterelor unui sir impartit la numarul de
componente, apoi creez un vector complex_string, in care voi retine componentele
si complexitatile acestor. Pentru a obtine o componenta se extrage din text,
incepand dintr-o anumita zona dimensiunea unei componente. Zona reprezinta un
numar care retine cate elemente au fost extrase, iar urmatoarea extragere se face
din acea zona a textului. Complexitatea unei componente se calculeaza apeland
functia double complexitate ( char* sir ).

Functia char* rearanjare ( complex_string* vect_comp_sort, int comp, 
long dim_text_cod_re ) aranjeaza componentele dupa regula specificata.

Pentru rezolvarea taskului se face mai intai conversia ultimului numar citit,
inainte de "END" din sir de caractere intr-un numar intreg apelandu-se functia
int string_to_int. Apoi se apeleaza functia complex_string* impartire_comp
pentru a imparti textul in componente. Se sorteaza componentele prin apelul
functiei complex_string* sortare si se aranjeaza dupa regula specificata
prin apelul functiei char* rearanjare. Apoi se afiseaza textul codificat
rearanjat.



La sfarsit se elibereaza memoria de pe heap.

Biblioteci folosite:
	- stdio.h
	- stdlib.h
	- string.h
	- ctype.h
