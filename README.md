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

Žemiau pateikti užfiksuoti rezultatų grafikai kiekvienam konteineriui:

### Pirma strategija

#### `vector<Student>`

![vector<Student> rezultatai](assets/student-vector.png)

#### `list<Student>`

![list<Student> rezultatai](assets/student-list.png)

#### `deque<Student>`

![deque<Student> rezultatai](assets/student-deque.png)

### Antra strategija

#### `vector<Student>`

![vector<Student> rezultatai 2](assets/student-vector-2.png)

#### `list<Student>`

![list<Student> rezultatai 2](assets/student-list-2.png)

#### `deque<Student>`

![deque<Student> rezultatai 2](assets/student-deque-2.png)

### Trečia strategija

#### `vector<Student>`

![vector<Student> rezultatai 3](assets/student-vector-3.png)

#### `list<Student>`

![list<Student> rezultatai 3](assets/student-list-3.png)

#### `deque<Student>`

![deque<Student> rezultatai 3](assets/student-deque-3.png)

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
