# Studentų valdymo programa

Tai C++17 projektas studentų duomenims nuskaityti, generuoti, rūšiuoti, skaidyti į dvi grupes ir išvesti į ekraną arba į failą. Programa palaiko kelis konteinerių tipus: `vector`, `list` ir `deque`.

## Funkcionalumas

- studentų įrašų nuskaitymas iš failo
- studentų kūrimas rankiniu būdu arba generuojant atsitiktinius duomenis
- galutinio pažymio skaičiavimas pagal vidurkį arba medianą
- studentų rūšiavimas pagal vardą, pavardę arba galutinį pažymį
- studentų skaidymas į `nuskriausti` ir `protingi`
- rezultatų išvedimas į ekraną arba į tekstinį failą
- testai didelėms duomenų imtims ir skirtingiems konteineriams

## Sistemos specifikacijos

Projektas buvo testuotas šioje aplinkoje:

| Paskirtis | Reikšmė |
| --- | --- |
| Operacinė sistema | Ubuntu 24.04.4 LTS |
| Branduolys | 6.17.0-20-generic |
| Kompiliatorius | g++ 13.3.0 |
| C++ standartas | C++17 |
| Procesorius | Intel Core i5-1035G1 @ 1.00 GHz |
| Operatyvioji atmintis | 7.3 GiB |
| Saugykla | SAMSUNG MZALQ256HAJD-000L2 NVMe SSD, 238.5 GB |

## Reikalavimai

- `g++` su C++17 palaikymu
- `make`

Greita patikra Linux aplinkoje:

```bash
g++ --version
make --version
```

## Kompiliavimas

1. Pereikite į projekto aplanką.
2. Surinkite programą su `make`.

```bash
cd /home/mantrimas/Documents/OOP/objektinis-programavimas
make
```

Tai sukuria vykdomąjį failą `student-vector`.

## Paleidimas

Paleiskite programą:

```bash
./student-vector
```

Išvalymas (jei reikia pilno perkompiliavimo):

```bash
make clean
```

Pilnas perkompiliavimas:

```bash
make clean && make
```

## Kaip paleisti našumo testus

Interaktyviame meniu pasirinkite:

1. `8 - Testuoti studentu skirstyma i nuskriaustus ir protingus`
2. Konteinerį:
	`1 - vector<Student>`
	`2 - list<Student>`
	`3 - deque<Student>`
3. Strategiją:
	`1 - Pirma`
	`2 - Antra`
	`3 - Trecia`

Testai paleidžiami failams:

- `students1000`
- `students10000`
- `students100000`
- `students1000000`
- `students10000000`

Programa pateikia laikus šioms dalims:

- failo nuskaitymas
- rūšiavimas
- skirstymas į `nuskriausti` ir `protingi`
- bendras laikas

## Testų rezultatų demonstracija

Žemiau pateikti užfiksuoti rezultatų laikai lentelėmis (vidurkiai per 5 iteracijas):

### Pirma strategija

#### `vector<Student>`

![vector<Student> rezultatai](assets/student-vector.png)

| Failas | Failo nuskaitymas (s) | Rūšiavimas (s) | Skirstymas į du konteinerius (s) | Iš viso (s) |
| --- | ---: | ---: | ---: | ---: |
| `students1000` | 0.005348 | 0.000910 | 0.000474 | 0.006732 |
| `students10000` | 0.040123 | 0.010939 | 0.004286 | 0.055347 |
| `students100000` | 0.401102 | 0.143412 | 0.049738 | 0.594252 |
| `students1000000` | 4.028192 | 1.857539 | 0.565715 | 6.451447 |
| `students10000000` | 43.320240 | 23.159201 | 6.503951 | 72.983393 |

#### `list<Student>`

![list<Student> rezultatai](assets/student-list.png)

| Failas | Failo nuskaitymas (s) | Rūšiavimas (s) | Skirstymas į du konteinerius (s) | Iš viso (s) |
| --- | ---: | ---: | ---: | ---: |
| `students1000` | 0.264378 | 0.000416 | 0.000417 | 0.265211 |
| `students10000` | 0.040764 | 0.005462 | 0.005061 | 0.051287 |
| `students100000` | 0.416849 | 0.079589 | 0.058335 | 0.554772 |
| `students1000000` | 4.277907 | 1.122498 | 0.628193 | 6.028598 |
| `students10000000` | 45.728463 | 15.337076 | 8.380724 | 69.446262 |

#### `deque<Student>`

![deque<Student> rezultatai](assets/student-deque.png)

| Failas | Failo nuskaitymas (s) | Rūšiavimas (s) | Skirstymas į du konteinerius (s) | Iš viso (s) |
| --- | ---: | ---: | ---: | ---: |
| `students1000` | 2.442345 | 0.000990 | 0.000362 | 2.443697 |
| `students10000` | 0.041081 | 0.012963 | 0.003810 | 0.057854 |
| `students100000` | 0.398689 | 0.167914 | 0.049400 | 0.616003 |
| `students1000000` | 4.063413 | 2.163593 | 0.525970 | 6.752976 |
| `students10000000` | 40.819395 | 26.040447 | 5.865333 | 72.725175 |

### Antra strategija

#### `vector<Student>`

![vector<Student> rezultatai 2](assets/student-vector-2.png)

| Failas | Failo nuskaitymas (s) | Rūšiavimas (s) | Skirstymas į du konteinerius (s) | Iš viso (s) |
| --- | ---: | ---: | ---: | ---: |
| `students1000` | 0.004007 | 0.000872 | 0.000344 | 0.005223 |
| `students10000` | 0.039909 | 0.010761 | 0.003104 | 0.053774 |
| `students100000` | 0.404832 | 0.146227 | 0.044469 | 0.595528 |
| `students1000000` | 4.443715 | 1.951990 | 0.555521 | 6.951227 |
| `students10000000` | 44.326327 | 23.175477 | 7.253997 | 74.755801 |

#### `list<Student>`

![list<Student> rezultatai 2](assets/student-list-2.png)

| Failas | Failo nuskaitymas (s) | Rūšiavimas (s) | Skirstymas į du konteinerius (s) | Iš viso (s) |
| --- | ---: | ---: | ---: | ---: |
| `students1000` | 0.286870 | 0.000371 | 0.000278 | 0.287519 |
| `students10000` | 0.039071 | 0.005386 | 0.003218 | 0.047675 |
| `students100000` | 0.400632 | 0.078744 | 0.057819 | 0.537194 |
| `students1000000` | 4.452552 | 1.286516 | 0.695090 | 6.434158 |
| `students10000000` | 42.211864 | 15.680675 | 7.077309 | 64.969847 |

#### `deque<Student>`

![deque<Student> rezultatai 2](assets/student-deque-2.png)

| Failas | Failo nuskaitymas (s) | Rūšiavimas (s) | Skirstymas į du konteinerius (s) | Iš viso (s) |
| --- | ---: | ---: | ---: | ---: |
| `students1000` | 0.011808 | 0.000961 | 0.000364 | 0.013133 |
| `students10000` | 0.039603 | 0.011673 | 0.002958 | 0.054233 |
| `students100000` | 0.380325 | 0.160646 | 0.050190 | 0.591161 |
| `students1000000` | 3.919922 | 2.027911 | 0.598699 | 6.546532 |
| `students10000000` | 40.708973 | 25.136992 | 6.387175 | 72.233141 |

### Trečia strategija

#### `vector<Student>`

![vector<Student> rezultatai 3](assets/student-vector-3.png)

| Failas | Failo nuskaitymas (s) | Rūšiavimas (s) | Skirstymas į du konteinerius (s) | Iš viso (s) |
| --- | ---: | ---: | ---: | ---: |
| `students1000` | 0.004231 | 0.001078 | 0.000841 | 0.006150 |
| `students10000` | 0.046350 | 0.010051 | 0.006671 | 0.063072 |
| `students100000` | 0.377915 | 0.139659 | 0.080396 | 0.597970 |
| `students1000000` | 3.887733 | 1.783990 | 0.835001 | 6.506724 |
| `students10000000` | 43.283007 | 24.787941 | 10.309531 | 78.380478 |

#### `list<Student>`

![list<Student> rezultatai 3](assets/student-list-3.png)

| Failas | Failo nuskaitymas (s) | Rūšiavimas (s) | Skirstymas į du konteinerius (s) | Iš viso (s) |
| --- | ---: | ---: | ---: | ---: |
| `students1000` | 1.561354 | 0.000375 | 0.047994 | 1.609723 |
| `students10000` | 0.039060 | 0.005398 | 0.067487 | 0.111945 |
| `students100000` | 0.413575 | 0.094919 | 0.133518 | 0.642012 |
| `students1000000` | 4.283401 | 1.266510 | 1.434149 | 6.984060 |
| `students10000000` | 43.516639 | 15.593472 | 14.049236 | 73.159348 |

#### `deque<Student>`

![deque<Student> rezultatai 3](assets/student-deque-3.png)

| Failas | Failo nuskaitymas (s) | Rūšiavimas (s) | Skirstymas į du konteinerius (s) | Iš viso (s) |
| --- | ---: | ---: | ---: | ---: |
| `students1000` | 0.004440 | 0.001544 | 0.000718 | 0.006701 |
| `students10000` | 0.037823 | 0.011935 | 0.006842 | 0.056600 |
| `students100000` | 0.379881 | 0.165033 | 0.083893 | 0.628808 |
| `students1000000` | 3.869504 | 2.117392 | 0.882899 | 6.869795 |
| `students10000000` | 39.435232 | 26.053171 | 9.309120 | 74.797523 |

Pastaba: rezultatai priklauso nuo aparatinės įrangos, kompiliatoriaus versijos, disko spartos ir tuo metu veikiančių foninių procesų.

## Išvados

Iš rezultatų matyti, kad strategijų skirtumai yra nuoseklūs visiems trims konteineriams: pirma strategija yra greičiausia, antra strategija dažniausiai užima vidurinę vietą, o trečia strategija yra lėčiausia.

Svarbiausia ne pats konteineris, o pasirinkta skaidymo strategija. Konteinerio tipas daro įtaką bendram laikui, bet strategijų tarpusavio skirtumas išlieka aiškiausias.

### Pirma strategija

- Pirmoji strategija pasirodė geriausiai: ji vieną kartą pereina per visus studentus ir sukuria du naujus konteinerius.
- Ji buvo greičiausia iš visų trijų, nes išvengia papildomo viso konteinerio skaidymo ir turi paprastesnį vykdymo kelią.

### Antra strategija

- Antroji strategija paprastai atsiduria per vidurį: ji tvarko elementus vietoje, bet vis tiek turi daugiau papildomų operacijų nei pirmoji strategija.
- Dėl to jos skirstymo laikas dažniausiai buvo tarp pirmos ir trečios strategijų.

### Trečia strategija

- Trečioji strategija buvo lėčiausia, nes ji pirmiausia atlieka papildomą viso konteinerio skaidymą, o po to dar kopijuoja rezultatus į naujus konteinerius.
- Dėl didesnio judinimo ir kopijavimo jos vykdymo laikas buvo didžiausias.

- Didėjant įvesčiai, visų strategijų trukmė sparčiai auga, o didžiausiuose failuose reikšmingą dalį vis tiek sudaro nuskaitymas iš disko.
- Patikimiausias palyginimas gaunamas tada, kai testai kartojami toje pačioje aplinkoje ir vertinamas ne tik bendras laikas, bet ir atskiros jo dalys.

## Struktūra

- `include/` - antraštiniai failai
- `src/` - pagrindinis programos kodas
- `assets/` - projekto vaizdai
- `data/` - pradiniai duomenų failai
- `students1000`, `students10000`, `students100000`, `students1000000`, `students10000000` - didelių imčių failai bandymams

## Pastabos

- Programa naudoja `make` failą surinkimui.
- Rikiavimas veikia tiek su `vector`, tiek su `list`, tiek su `deque`.
- Didelių duomenų imčių testai skirti palyginti nuskaitymo, rūšiavimo ir skaidymo laikus.
