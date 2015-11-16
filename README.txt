	Elemente de graficã pe calculator - Tema 4
******************************************************************************************

	View Frustum Culling
	Despa Diana Alexandra 331CA

******************************************************************************************

	Cuprins
1. Cerinta
2. Utilizare
3. Implementare
4. Testare
5. Probleme Aparute
6. Continutul Arhivei
7. Functionalitati
8. Mentiuni

******************************************************************************************

1. Cerinta
	Tema presupune implementarea algoritmului de frustum culling pe o scena 3D cu
foarte multe obiecte, iluminata cu o lumina de tip spot.

******************************************************************************************

2. Utilizare
	Programul se ruleaza prin lansarea executabilului Tema4.exe, din folderul Debug,
sau din interiorul Visual Studio.
	
Taste:
	Esc - inchidere program
	SHIFT + W - comutare intre desenare fill si wireframe
	C - comuta intre camere
	W - translateaza camera FPS inainte
	S - translateaza camera FPS inapoi
	Q - translateaza camera FPS in sus
	E - translateaza camera FPS in jos
	A - translateaza camera FPS stanga
	D - translateaza camera FPS dreapta
	1 - roteste ultima camera FPS in sens antitrigonometric
	2 - roteste ultima camera FPS in sens trigonometric
	3 - roteste ultima camera FPS stanga
	4 - roteste ultima camera FPS dreapta
	5 - roteste ultima camera FPS in sus
	6 - roteste ultima camera FPS in jos
	F1 - activeaza full screen
	F2 - dezactiveaza full screen

******************************************************************************************

3. Implementare
	Ca IDE, am folosit Microsoft Visual Studio 2013, instalat pe Windows 7, insa am
implementat aplicatia folosind Visual C++ 2010, ca sa ma asigur ca functioneaza cu
versiuni mai recente de Visual C++.
	Am pornit cu implementarea de la framework-ul laboratorului 7 si 8.
	Obiectele ce compun scena sunt construite folosind VAO, VBO si IBO.
	Scena este formata din mai multe cladiri asemanatoare, un teren/quad pe care sunt
plasate si vehiculul fix fata de camera view1. Generez 2500 (50x50) obiecte, care
formeaza "orasul". Fiecare cladire are dimensiunile gerate aleator, intre anumite limite,
si este texturata cu o textura aleatoare dintre cele 5 incarcate de mine.
	Deplasarea camerei view1 se realizeaza conform enuntului. Vehiculul are o pozitie
fixa fata de aceasta camera, deoarece este desenat cu o matrice de vizualizare constanta.
Obiectele sunt desenate "normal" din perspectiva view1, adica texturate sau cu culorile
originale ale vertecsilor. In functie de variabila uniforma "has_color" din fragment
shader pot determina daca un obiect este texturat sau pur si simplu colorat.
	Camera view2 cuprinde tot orasul. Atunci cand ea este activata, toate cladirile
sunt desenate, avand culoarea determinata de variabila uniforma "tps_color" din vertex
shader, in functie de vizibilitatea cladirii fata de view frustum.
	Algoritmul de view frustum culling urmeaza indicatiile din enunt. Am extras
coeficientii ecuatiilor planelor care formeaza frustum-ul din matricea de proiectie-
-vizualizare (pentru a nu inmulti de fiecare data si cu matricea de modelare, lucrez cu
pozitiile vertecsilor obiectelor din scena inmultite cu matricea de modelare a fiecaruia,
ele fiind fixe pe durata rularii programului). Am utilizat notiunile prezentate intr-un
document online*, pentru a determina ecuatiile fiecarui plan scazand sau adunand linii
din produsul celor 2 matrice. Determin daca un varf este in interiorul planului prin
inlocuirea coordonatelor varfului in ecuatia planului si verificarea semnului
rezultatului: daca este pozitiv, varful se afla in interior, altfel se afla in exterior.
	Iluminarea scenei o realizez cu modelul Phong, am implemenetat efectul de tip
spotlight conform indicatiilor din laboratorul "Iluminare folosing GLSL". Prin compararea
cosinusului unghiului luminii de la sursa (cutoff) cu produsul scalar dintre vectorul
directiei de la sursa luminii la un anumit punct si vectorul directiei luminii (aceeasi
cu a camerei view1), pot spune daca acel punct este iluminat sau nu. Din perspectiva
view2, scena nu este iluminata. Vehiculul nu este iluminat niciodata si nu este desenat
din perspectiva view2.

******************************************************************************************

4. Testare
	Am testat fiecare nou feature implementat: deplasarea camerei, deplasarea
vehiculului odata cu camera prin miscarea camerei, generarea cladirilor prin explorarea
scenei, lumina de tip spot prin miscarea camerei, algoritmul de frustum culling si
functionalitatea celei de-a doua perspective de asemenea prin miscarea camerei. Am folosit
si afisari la consola pentru debugging. Nu am utilizat teste automate. Am utilizat
debugger-ul din Visual Studio.

******************************************************************************************

5. Probleme aparute
	Deplasarea obiectului cu pozitie fixa fata de camera FPS a fost dificil de
implementat la inceput, nu am reusit sa fac astfel incat acel obiect sa se deplaseze in
spatiului celorlalte obiecte si sa urmareasca totodata miscarile camerei, dar am realizat
ca matricea de vizualizare dicteaza modul in care un obiect este plasat fata de camera
asa ca obiectul meu are propria lui matrice de vizualizare, diferita de cea a celorlalte.
	Nu am realizat foarte repede ca pentru tipul matrice din glm, mat4, accesarea
elementelor se face intai dupa coloana si apoi dupa linie, asta a creeat ceva probleme
la extragerea coeficientilor planurilor frustumului din matricea de proiectie-vizualizare-
modelare.

******************************************************************************************

6. Continutul Arhivei
	main.cpp - sursa principala
	Building.cpp
	Building.h
	City.cpp
	City.h
	MyVertexFormat.h
	PlaneExtractUtil.cpp
	PlaneExtractUtil.h
	Quad.cpp
	Quad.h
	Vehicle.cpp
	Vehicle.h
	Framework-ul de la laborator.
	README - acest fisier.

******************************************************************************************

7. Functionalitati
	Functionalitati Standard
		Desenarea obiectelor scenei
		Obiecte texturate
		Iluminare de tip spot
		Camerele view1 si view2
		View frustum culling

	Functionalitati Suplimentare
		Desenare quad/teren
		Dimensiunile si texturile alese pentru fiecare cladire sunt aleatorii
		
******************************************************************************************

8. Mentiuni
	Initializarea programului dureaza cateva secunde deorece incarc un mesh foarte
complex, cu multe poligoane, pentru vehicul.
	Majoritatea comentariilor din cod, in special cele care descriu metode si membri
ale claselor implementate se afla in fisierele de tip header.
	Am descarcat fisiere .obj folosite de pe site-ul http://tf3dm.com/
	Am descarcat texturile cladirilor de pe diverse site-uri de imagini.
*	Am implementat algoritmul folosind notiunilor prezentate in documentul:
http://web.archive.org/web/20120531231005/http://crazyjoke.free.fr/doc/3D/plane%20extraction.pdf