# Dane autora
- **imię i nazwisko:** Michał Gryglicki
- **Numer indeksu:** 331380

# Założenia:
1) Dodawanie słowa do licznika słów w czasie stałym (prawie).
2) Wyszukiwanie słowa w liczniku w czasie stałym (prawie).
3) Iterator leksykograficzny na słowa typu constant (zakaz modyfikowania licznika podczas iteracji)
4) Iterator częstości wystąpień na słowa typu constant (zakaz modyfikowania licznika podczas iteracji)

# Realizacja:
Słowa w licznku są przechowywane w wektorze (std::vector) w kolejności dodawania do licznika

## Wyszukiwanie / Dodawanie słów do licznika
Wprowadziłem tablice hashująco-łańcuchową, która dla danego słowa (string) zwraca listę indeksów, pośród których znajduje się indeks szukanego słowa. Dobranie odpowiednio dużego rozmiaru tablicy hashującej pozwala na osiągnięcie efektu prawie stałej złożoności czasowej w dostępie do wyszukiwanego słowa (Entry). Dzieje się tak, gdyż
>[wektor wszystkich Entry].size() << [wektor zwracany przez tablice hashującą].size()

## Iteracja leksykograficzna
Przy tworzeniu iteratora, tworzy on wektor iteratorów do wektora słów (counter), a następnie sortuje go leksykograficznie, iteracja polega na pobraniu kolejnego iteratora z wektora iteratorów.

Zdaję sobie sprawę, że może właściwszym rozwiązaniem byłoby trzymanie posortowanego wektora słów w counter-rze. Z pewnością oba podejścia mają swoje wady i zalety, których części byłem, a części nie byłem świadomy podczas podejmowania tej istotnej decyzji projektowej. Zdecydowałem się na takie rozwiązanie, głównie dlatego aby
program był wydajny dla dużej liczby wprowadzanych słów. Gwarantuje to tablica hashująca-łańcuchowa i dostęp do słowa w czasie praktycznie stałym. Przyjąłem heurystykę, że jeśli program ma służyć do liczenia wystąpień poszczególnych słów to te same słowa będą pojawiały się kilka razy (inaczej nie ma sensu liczenie krotności ich występowania). Co więcej najczęściej będzie tak, że `liczba wszystkich słów << liczby różnych słów`, więc każdorazowe szukanie oraz ustanawianie porządku w tablicy przy dodawaniu nowego słowa wydaje się być większym obciążeniem niż posortowanie stosunkowo małego wektora słów w momencie gdy tego potrzebujemy. Mimo to, nawet mnie do końca nie przekonuje ta konstrukcja, mam wrażenie że trzymając w iteratorze wektor iteratorów poniekąd tracimy istotę jego funkcjonowania. Problemem staje się także operator postinkrementacji, który zwraca kopię iteratora - iterator zajmuje więcej pamięci, więc i jego kopiowanie trwa dłużej.

## Iteracja częstości wystąpień
Iteracja odbywa się po kolejnych elementach countera, jeśli napotkane zostanie słowo o takiej samej częstości jak aktualnie wskazywane to iterator zostaje przestawiony, w przeciwnym razie iterator jest ustawiany na słowo o największej częstości występowania mniejszej od częstości wystęĻowania aktualnie wskazywanego

# Statystyki
Pomimo trzymania wektora słów w counter-rze w kolejności dodawania, a nie leksykograficznie, osiągnięte przez mnie wyniki wydają się być satysfakcjonujące. Widać, że główne założenie, czyli dodawanie/wyszukiwanie słowa w czasie stałym udało się zrealizować - dla 10-krotnie większego(kopie) pliku moby_dick.txt czas tworzenia counter-a wzrasta liniowo.
```
Testowano na maszynie z układem APPLE M2

moby_dick.txt

Creation time: 76 ms.
Lexicographical iteration time (pre-incrementation): 23 ms.
Lexicographical iteration time (pre-incrementation): 1611 ms.
Frequency iteration time: 96 ms.


10x moby_dick.txt

Creation time: 652 ms.
Lexicographical iteration time (pre-incrementation): 23 ms.
Lexicographical iteration time (pre-incrementation): 1616 ms.
Frequency iteration time: 95 ms.
```
