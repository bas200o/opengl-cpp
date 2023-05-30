# Requirements checklist

## OpenGL

### Must
| Name                                                           | realized | loaction              |
|----------------------------------------------------------------|----------|-----------------------|
| OpenGL gebruiken voor het weergeven van 3D graphics            | ja       | Main.cpp int main()   |
| Een camera hebben die bestuurd kan worden                      | ja       | FpsCam.cpp update()   |
| Minimaal 5 verschillende objecten bevatten                     | ja       | Main.cpp initModels() |
| Een of meerdere objecten bewegen automatisch                   | ja       | FpsCam.cpp update()   |
| Een of meerdere objecten zijn door de gebruiker te beïnvloeden | ja       | FpsCam.cpp update()   |
| Een van de objecten is een ‘complex’ object                    | ja       | Main.cpp update()     |
| Belichting gebruiken                                           | ja       | Main.cpp init()       |
| Texture mapping gebruiken                                      | ja       | Main.cpp init()       |

### Could
| name                                 | achieved | location              |
|--------------------------------------|----------|-----------------------|
| Een complexe scene met meer objecten | ja       | Main.cpp initModels() |
| Een samenhangende scene              | ja       | "                     |
| Gebruik van mist                     | nee      |                       |
| Alpha blending                       | nee      |                       |
| 2D overlay                           | nee      |                       |
| Relatieve transformaties             | nee      |                       |
| Particle systemen                    | nee      |                       |

## C++
| name                                                                                                                                                | achieved | location                          |
|-----------------------------------------------------------------------------------------------------------------------------------------------------|----------|-----------------------------------|
| De code bevat geen overbodige #defines en bevat geen magische constanten.                                                                           | ja       | nvt                               |
| Gebruik maken van OO-principes in C++, zoals gebruik van klassen met constructors en destructors, polymorfisme en/of inheritance                    | ja       | Vehicle.cpp move()                |
| De code gebruikt op ten minste 1 plek op een zinnige wijze van overerving en virtuele functie(s).                                                   | ja       | drawable.hpp                      |
| De code heeft ten minste 1 unit-test waarbij het resultaat in een bestand wordt weggeschreven.                                                      |     ja     |            test.cpp           |
| Met behulp van FileIO, bestanden kunnen lezen en schrijven                                                                                          | ja       | Main.cpp readScore()/writeScore() |
| Toepassen van standaard datastructuren in C++.                                                                                                      | ja       |                                   |
| Gebruik maken van streams.                                                                                                                          | ja       | main.cpp readScore()              |
| Rekening gehouden met het voorkomen van memory leaks.                                                                                               | ja       |                                   |
| Zinnige foutmeldingen mocht er iets fout gaan, afhandeling via exceptions                                                                           | ja       | main.cpp main()                   |
| Gebruik maken van C++ standaard, dus niet op C manier alloceren.                                                                                    | ja       |                                   |
| Weloverwogen gebruik van algoritmes binnen de applicatie                                                                                            | ja       | main.cpp update()                 |
| Maak de omzetting van een variabele door middel van een literal operator zinniger                                                                   |      ja    |       main.cpp               |
| De documentatie bevat een overzichtstabel waarin staat aan welke criteria de code voldoet, en, voor zover zinnig, specifiek welke delen van de code | ja       | requirements.md                   |

### could
| name                                                                                                    | achieved    | location          |
|---------------------------------------------------------------------------------------------------------|-------------|-------------------|
| De applicatie leest gegevens in vanuit een tekst-file naar in-memory data, volgens het factory pattern. | nee         |                   |
| Smart pointers                                                                                          | nee         |                   |
| Gebruik maken van Template Metaprogramming                                                              | nee         |                   |
| Ervoor zorgen dat je programma const, constexpr en override correct is                                  | nee         |                   |
| Lambda expressies, denk hierbij ook aan een typedef                                                     | ja          | main.cpp update() |
| Pointer to implementation, scherm een structure of klasse af.                                           | nee         |                   |
| Proxy-patroon: Protection proxy                                                                         | nee         |                   |
| Nested datatypes                                                                                        | nee         |                   |
| De code voldoet aantoonbaar aan andere, wenselijke (kwaliteit verhogende) en gespecificeerde criteria.  | voor docent |                   |