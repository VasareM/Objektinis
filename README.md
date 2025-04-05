## Sistemos parametrai
| CPU               | RAM   | SSD         |
|-------------------|-------|-------------|
| i5-1240P 1.70 GHz | 16 GB | SSD 512 GB  |


### Tyrimo rezultatai: *testuojami anksčiau sugeneruoti failai*
Legenda:
- melsvai paryškintas testuojamo failo įrašų kiekis

#### Testuojami paeiliui su 1000, 10000, 100000, 1000000, 10000000 eilučių failais, trijuose skirtinguose konteineriuose, trimis skirtingomis strategijomis
1 strategija: Bendro studentai konteinerio skaidymas į du naujus to paties tipo konteinerius;

2 strategija: Bendro studentų konteinerio skaidymas panaudojant tik vieną naują konteinerį (kiti šalinami iš bendro);

3 strategija: Bendro studentų konteinerio skaidymas panaudojant greičiausiai veikiančią (1 strategiją), į ją  įtraukiant į ją „efektyvius“ darbo su konteineriais metodus.
![Image](https://github.com/user-attachments/assets/b7fafe09-36fe-4d07-957d-9479f319d84b)

### Instrukcija
programą galima paleisti dviem būdais
1. sukompiliuojant komandinėje eilutėje

   ***į terminalą reikia įrašyti:***
   
   g++ kodas_vektoriai.cpp funkcijos.cpp -o prog
   
   ./prog
   
2. naudojant **cmake** failą

   ***į terminalą reikia įrašyti (jei kompiliuojama nauja programa):***
   
   rm -r build  *(jei jau turimas build aplankas, nerašyti jei kompiliuojama pirmą kartą)*

   mkdir build

   cd build

   cmake ..

   cmake --build . *(kompiliuoja)*
   cd Debug   *(be jo po pertraukos neveikė)*
   .\Objektinis.exe *(paleidžia programą)*
   
