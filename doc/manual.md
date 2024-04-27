---
title: "Ćwiczenie 13: Minimalizacja rozmiaru programu"
subtitle: "Instrukcja laboratorium"
footer-left: "Instrukcja laboratorium"
author: [Mariusz Chilmon <<mariusz.chilmon@ctm.gdynia.pl>>]
lang: "pl"
titlepage: yes
titlepage-logo: "logo.png"
logo-width: "70mm"
colorlinks: yes
header-includes: |
  \usepackage{awesomebox}
  \usepackage{algorithm}
  \usepackage{algpseudocode}
  \usepackage{tikz}
  \usepackage{xfrac}
  \usepackage{ellipsis}
  \usetikzlibrary{positioning}
  \usepackage[raster]{tcolorbox}
  \usepackage{lcd}
  \LCDcolors[MidnightBlue]{MidnightBlue!10}{MidnightBlue!80}
...

\lstset{language=[11]C++}

> One of my most productive days was throwing away 1000 lines of code.
>
> — _Kenneth Lane Thompson_

# Cel ćwiczenia

Celem ćwiczenia jest zapoznanie się z:

* poziomami optymalizacji kompilatora GCC,
* kosztem obliczeń zmiennoprzecinkowych,
* kosztem pełnej implementacji funkcji z rodziny `printf()`.

# Uruchomienie programu wyjściowego

1. Podłącz płytkę _LCD Keypad Shield_ do _Arduino Uno_.
1. Podłącz termometr LM35DZ do linii _A5_.
1. Na wyświetlaczu widoczny jest odczyt wartości z ADC, mierzącego napięcie z termometru scalonego LM35DZ, i obliczona na tej podstawie temperatura.
1. **Zapisz w sprawozdaniu wyjściowy rozmiar programu (wersja zmiennoprzecinkowa).**

\DefineLCDchar{degree}{00010001010001000000000000000000000}
\begin{center}
\LCD{2}{16}
    |ADC: 204        |
    |TEMP:21.91{degree}C    |
\captionof{figure}{Wyjściowy stan wyświetlacza}
\end{center}

# Zadanie podstawowe

Celem zadania podstawowego jest zmniejszenie rozmiaru programu przez zastąpienie obliczeń zmiennoprzecinkowych obliczeniami na liczbach całkowitych. 

## Wymagania funkcjonalne

1. Funkcjowanie urządzenia nie zmienia się[^1].
1. Następuje zmniejszenie rozmiaru programu o około 400&nbsp;B…500&nbsp;B.

[^1]: Wynik pomiaru może różnić się o 0,01\textcelsius{ } ze względu na brak zaokrąglania przy obliczeniach całkowitych.

## Modyfikacja programu

### Opis rozwiązania wyjściowego (operacji zmiennoprzecinkowych)

Zależność między odczytem $ADC$ z 10-bitowego przetwornika analogowo-cyfrowego a&nbsp;temperaturą&nbsp;$T$, wyznaczona w&nbsp;oparciu o&nbsp;dokumentację ADC oraz termometru scalonego LM35DZ, wyraża się wzorem:

\begin{equation}
T = \frac{V_{REF}\cdot ADC}{2^{10}} \cdot 100\frac{\text{\textcelsius}}{\text{V}}
\end{equation}

co przy napięciu referencyjnym 1,1&nbsp;V daje:

\begin{equation}
T = \frac{1{,}1\cdot ADC}{1024} \cdot 100\text{\textcelsius}
\end{equation}

z czego wynika:

```
double temperature = 1.1 * measurement / 1024 * 100;
```

co z kolei można zamienić na tekst w buforze `char buf[]` za pomocą funkcji `snprintf()`:

```
snprintf(buf, sizeof(buf), "%5.2f", temperature);
```

która wartość zmiennoprzecinkową `temperature` formatuje do postaci tekstowej za pomocą parametru `"%5.2f"`:

\begin{description}
\item[\%]
Prefiks oznaczający pole formatujące.
\item[5]
Szerokość pola (tu: 5 znaków, włącznie z kropką dziesiętną).
\item[.2]
Precyzja — liczba cyfr części ułamkowej (tu: 2 miejsca po przecinku).
\item[f]
Formatowanie liczby zmiennoprzecinkowej do formatu ułamka dziesiętnego.
\end{description}

### Zamiana obliczeń zmiennoprzecinkowych na całkowite

Zauważ, że w ramach określonej precyzji wyniku można zastąpić obliczenia zmiennoprzecinkowe obliczeniami na liczbach całkowitych, np. obliczenia na długościach wyrażonych w ułamkach metra można zastąpić obliczeniami na tych samych długościach wyrażonych w milimetrach — jeżeli nie dochodzi do utraty dokładności, jest to tylko zmiana sposobu zapisu liczb.

Weźmy na przykład obliczenia:
 
```
double result = 3.14 * 1.42;
printf("%5.3f\n", result);
// Wynik: "4.459"
```

Możemy przeskalować wartości ułamkowe do wartości całkowitych, a wynik wyświetlić jako dwie liczby całkowite oddzielone kropką. Przed kropką mamy część całkowitą uzyskaną za pomocą dzielenia całkowitego `fixed / 1000` zaś za kropką mamy część ułamkową, która jest resztą z tego dzielenia `fixed % 1000`.

Należy tylko zauważyć, że pomnożyliśmy obie stałe przez 100, więc wynik jest $100 \cdot 100 = 10000$ razy większy od oczekiwanego. Ponieważ na potrzeby wyświetlania dzielimy go tylko przez 1000, należy go jeszcze przeskalować o rząd wielkości dzieląc przez dziesięć.

```
uint32_t fixed = 314 * 142 / 10;
printf("%1u.%03u\n", fixed / 1000, fixed % 1000);
// Wynik: "4.458"
```

\awesomebox[teal]{2pt}{\faCode}{teal}{Wynik różni się na najmniej znaczącej pozycji ze względu na to, że dzielenie całkowite odrzuca część ułamkową (ignoruje resztę z dzielenia), nie dokonując zaokrąglenia. Akceptujemy ten błąd na potrzeby ćwiczenia, można go jednak obsłużyć, samodzielnie implementując zaokrąglenie.}

Przeprowadź analogiczną redukcję obliczeń pomiaru temperatury w funkcji `printMeasurement()`, zmieniając wartość zmiennoprzecinkową `1.1` na wartość całkowitą.

W razie problemów pamiętaj, że:

1. Dzielenie całkowite odrzuca część ułamkową, obniżając precyzję obliczeń, więc najlepiej wykonywać je na końcu.
1. Nawet jeżeli ostateczny wynik obliczeń mieści się w zakresie np. typu `uint16_t`, to pośrednie obliczenia mogą ten typ przepełnić.
1. Kompilator dobiera typ stosowany do obliczeń na podstawie pierwszej wartości w ciągu obliczeń.
1. Dla kompilatora AVR-GCC typem domyślnym jest 16-bitowy `int` ze znakiem (`int16_t`), którego zakres jest znacznie mniejszy od 32-bitowego czy 64-bitowego stosowanego w komputerach PC.
1. Aby nastąpiła redukcja rozmiar programu, nie może on w żadnym miejscu wykonywać operacji zmiennoprzecinkowych.

\awesomebox[teal]{2pt}{\faCode}{teal}{Można wymusić na kompilatorze stosowanie szerszego typu. Wyrażenie \lstinline{1000 * 1000 / 1000} da nieprawidłowy wynik 16, gdyż liczba 1~000~000, będąca wynikiem mnożenia, nie mieści się w zakresie \lstinline{int16_t}. Prawidłowy wynik można uzyskać, każąc zacząć obliczenia na typie \lstinline{uint32_t} za pomocą wyrażenia \lstinline{UINT32_C(1000) * 1000 / 1000}.}

# Zadanie rozszerzone

Celem zadania rozszerzonego jest zmniejszenie rozmiaru programu przez użycie odpowiednich flag kompilatora i linkera.

## Wymagania funkcjonalne

1. Funkcjowanie urządzenia nie zmienia się.
1. Następuje zmniejszenie rozmiaru programu.

## Modyfikacja programu

### Dobranie poziomu optymalizacji kompilatora

Znajdź w pliku \texttt{Makefile} zmienną `OPTIMIZATION` i sprawdź jej wpływ na rozmiar programu, korzystając z tabeli w sprawozdaniu.

\awesomebox[teal]{2pt}{\faCode}{teal}{Plik \texttt{Makefile} odpowiedzialny jest za śledzenie zmian w kodzie źródłowym i nie wykrywa on zmian w samym sobie. Oznacza to, że przed każdym zbudowaniem programu należy wywołać zadanie \lstinline{clean}, żeby kompilacja przebiegła od początku.}

### Użycie uproszczonej implementacji funkcji rodziny `printf()`

Po zmianie obliczeń ze zmiennoprzecinkowych na stałoprzecinkowe możliwe jest użycie biblioteki z uproszczonymi funkcjami rodziny `printf()`. W tym celu z pliku \texttt{Makefile} należy usunąć linię z&nbsp;flagami linkera, które nakazują mu użycie biblioteki wspierającej operacje zmiennoprzecinkowe zamiast domyślnej, uproszczonej:

```Makefile
LDFLAGS += -Wl,-u,vfprintf -lprintf_flt
```

\awesomebox[teal]{2pt}{\faCode}{teal}{Pełna implementacja funkcji \lstinline{printf()} jest bardzo wymagająca, gdyż osbługuje wiele formatów. Szczególnie wymagające jest formatowanie typów zmiennoprzecinkowych ze względu na możliwości standardu IEEE~754 oraz złożoność obliczeń potrzebnych do obsługi różnych sposobów reprezentacji ułamków. Z tego powodu w systemach wbudowanych często stosuje się zredukowane biblioteki standardowe.}
