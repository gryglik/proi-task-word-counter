# Dane autora
- **imię i nazwisko:** Michał Gryglicki
- **Numer indeksu:** 331380

# Założenia:
1) Dodawanie słów do licznika słów w czasie stałym (prawie).
2) Wyszukiwanie słów w liczniku w czasie stałym (prawie).
3) Iterator leksykograficzny na słowa typu constant (zakaz modyfikowania licznika podczas iteracji)
4) Iterator częstości wystąpień na słowa typu constant (zakaz modyfikowania licznika podczas iteracji)

# Realizacja:
Słowa w licznku są przechowywane w wektorze (std::vector) w kolejności dodawania do licznika

## Wyszukiwanie / Dodawanie słów do licznika
Wprowadziłem tablice hashująco-łańcuchową, która dla danego słowa (string) zwraca listę indeksów, pośród których znajduje się indeks szukanego słowa. Dobranie odpowiednio dużego rozmiaru tablicy hashującej pozwala na osiągnięcie efektu prawie stałej złożoności czasowej w dostępie do wyszukiwanego słowa (Entry). Dzieje się tak, gdyż
>[wektor wszystkich Entry].size() << [wektor zwracany przez tablice hashującą].size()

## Iteracja leksykograficzna

## Iteracja częstości wystąpień

# Statystyki
```
Creation time: 73 ms.
Lexicographical iteration time: 3 ms.
Frequency iteration time: 84 ms.
```
