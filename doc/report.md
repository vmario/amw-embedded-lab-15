---
title: "Ćwiczenie 13: Minimalizacja rozmiaru programu"
author: [Mariusz Chilmon <<mariusz.chilmon@ctm.gdynia.pl>>]
lang: "pl"
titlepage: no
colorlinks: yes
header-right: "\\faEdit"
footer-left: "Sprawozdanie z laboratorium"
header-includes: |
  \usepackage{awesomebox}
  \usepackage{tikz}
  \usepackage{xfrac}
  \usetikzlibrary{positioning}
  \usetikzlibrary{positioning}
  \usepackage[raster]{tcolorbox}
...

\lstset{language=[11]C++}

_W trosce o Państwa wyniki proszę o czytelne wpisywanie nazwisk._

**Data**: \dotfill

**Autorzy**: \dotfill

# Część praktyczna

## Zadanie podstawowe

**Ocena prowadzącego**: \dotfill

## Zadanie rozszerzone

**Ocena prowadzącego**: \dotfill

# Część teoretyczna

## Zadanie podstawowe

Odczytaj z komunikatów procesu kompilacji rozmiar programu w pamięci Flash (\texttt{Program}) i rozmiar danych w pamięci RAM (\texttt{Data}) dla obu wersji programu.

\begin{center}
\begin{tabular}{|c|c|c|} 
\hline
\textbf{Obliczenia} & \textbf{Rozmiar programu} & \textbf{Rozmiar danych} \\
\hline
zmiennoprzecinkowe & \hphantom{WWWWWWWWWW} & \hphantom{WWWWWWWWWW} \\
\hline
całkowite &  & \\
\hline
\end{tabular}
\end{center}

## Zadanie rozszerzone

Odczytaj z komunikatów procesu kompilacji rozmiar programu w pamięci Flash (\texttt{Program}) i rozmiar danych w pamięci RAM (\texttt{Data}) dla obu wersji programu.

\begin{center}
\begin{tabular}{|c|c|c|} 
\hline
\textbf{Poziom optymalizacji} & \textbf{Rozmiar programu} & \textbf{Rozmiar danych} \\
\hline
\texttt{-O0} & \hphantom{WWWWWWWWWW} & \hphantom{WWWWWWWWWW} \\
\hline
\texttt{-O1} &  & \\
\hline
\texttt{-O2} &  & \\
\hline
\texttt{-Os} &  & \\
\hline
\end{tabular}
\end{center}

Odczytaj z komunikatów procesu kompilacji rozmiar programu w pamięci Flash (\texttt{Program}) i rozmiar danych w pamięci RAM (\texttt{Data}) dla obu wersji programu.

\begin{center}
\begin{tabular}{|c|c|c|} 
\hline
\textbf{Biblioteka \texttt{printf}} & \textbf{Rozmiar programu} & \textbf{Rozmiar danych} \\
\hline
zmiennoprzecinkowa & \hphantom{WWWWWWWWWW} & \hphantom{WWWWWWWWWW} \\
\hline
uproszczona &  & \\
\hline
\end{tabular}
\end{center}

## \faCertificate&nbsp; Zadanie specjalne

_+1 pkt dla osoby, która jako pierwsza poda poprawną odpowiedź._

Dlaczego wynikiem wyrażenia `1000 * 1000 / 1000` jest 16? (Podaj przebieg obliczeń prowadzących do tego wyniku).
