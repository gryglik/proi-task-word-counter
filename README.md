# words counter
Zadaniem jest przygotowanie licznika słów, który posłuży do analizy częstości występowania słów w różnych pracach.
W pierwszym kroku trzeba spisać, jaką funkcjonalność powinna realizować klasa licznika:
- dodanie słowa,
- dodanie słów odczytywanych ze strumienia,
- wyczyszczenie zawartości licznika,
- dodanie słów z innego licznika,
- zapis zawartości licznika do pliku,
- odczyt zawartości licznika z pliku,
- iterator przechodzący przez słowa alfabetycznie,
- iterator przechodzący przez słowa wg częstości wystąpień (od najczęściej występującego słowa).

Wygląda na to, że słowo i liczba jego wystąpień będą podstawowym elementem, który powinniśmy składać w kolekcji. Mamy zatem do napisania klasę reprezentującą element kolekcji (powiedzmy, że będzie nazywać się entry) i wybranie kolekcji z biblioteki standardowej. Zgodnie z ogólnymi zaleceniami, jeśli nie ma istotnych przesłanek przeciw, powinniśmy wybrać vector

Proszę zdefiniować klasę entry ze składowymi value (typu std::string) i count (typu int).
Prócz konstruktorów (jakich?) w klasie będą potrzebne:

- operator ++ (w wersji post), który zwiększa o 1 składową count;
- jednoargumentowy operator * (operator wyłuskania), który zwróci ustaloną referencję na składową value;
- operator konwersji na typ int zwracający wartość składowej count;
- operatory wyprowadzania << na strumień i wprowadzania << ze strumienia kompatybilne ze sobą (to nie mogą być metody klasy, ale będziemy tych operatorów potrzebować)

Proszę zdefiniować klasę word_counter z prywatną składową, która jest wektorem obiektów typu entry. Czy potrzebujemy w tej klasie konstruktora domyślnego? Jaki stan licznika słów powinien być obserwowany po utworzeniu domyślnego licznika? Jak ten stan sprawdzić?


