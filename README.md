Prosjekt: Tastatur styrt med AVR mikrokontrollere
Student: Anders Kristoffersen
Veileder: Terje Mathiesen
Kontaktperson hos problemeier: Atle Dyrnes

# Innhold

1. [Problemstilling](#1-problemstilling)
    - 1.1 [Overordnet problemstilling](#11-overordnet-problemstilling)
    - 1.2 [Endelig spesifikasjon](#12-endelig-spesifikasjon)
2. [Løsning](#2-løsning)
    - 1.3 [Konsept](#13-konsept)
    - 1.4 [Maskinvare](#14-maskinvare)
        - 1.4.1 [Design](#141-design)
        - 1.4.2 [Implementasjon](#142-implementasjon)
    - 1.5 [Fastvare](#15-fastvare)
        - 1.5.1 [Design](#151-design)
        - 1.5.2 [Implementasjon](#152-implementasjon)
3. [Verifikasjon og testing](#3-verifikasjon-og-testing)
   - 1.6 [Kretstesting](#16-kretstesting)
   - 1.7 [Fastvaretesting](#17-fastvaretesting)
4. [Konklusjon](#4-konklusjon)
-  [Referanser](#referanser)
- [Vedlegg A](#vedlegg-a)
   - GitHub-depot
- [Vedlegg B](#vedlegg-b)
   - Tegninger av kretsdiagram
- [Vedlegg C](#vedlegg-c)
   - Tegninger av kretskort
- [Vedlegg D](#vedlegg-d)
   - Bilder av ferdig loddet tastatur

# 1 Problemstilling

## 1.1 Overordnet problemstilling

Å bygge et tastatur med egenutviklet fastvare og utforming spesifisert helt til ens egne
ønsker.

## 1.2 Endelig spesifikasjon

Tastaturet skal fungere i stor grad som et normalt tastatur med tall-, bokstav og vanlige
spesialtaster men med mulighet for å programmere fastvaren til det en selv ønsker.
Utformingen på tastaturet skal gi gode forhold for komfort og helse for en som bruker
tastatur i lange perioder om gangen. Tastaturet skal være styrt av en eller flere AVR
mikrokontrollere og kommunikasjon til PC skal skje over USB.

# 2 Løsning

## 1.3 Konsept

Første steg i prosjektet ble å utforske ulike løsninger som er blitt gjort tidligere. Det
vanligste valget når en skal designe sitt eget tastatur var å bruke et relativt ferdig
System On Chip (SOC) som f.eks. Pro Micro og benytte seg av ferdigutviklet fastvare som
QMK. Men her ønsket jeg heller å utvikle min egen fastvare og starte designet mitt med
utgangspunkt i en enkeltstående AVR mikrokontroller.

Den største fordelen med å utvikle egen fastvare er tilpasningsmulighetene det gir.
Derfor ønsket jeg også å inkludere noen tilkoblingsmuligheter til tastaturet som gir
muligheten til å utvikle svært frie utvidelser til tastaturet i fremtiden.

I tillegg måtte utformingen på tastaturet bestemmes og da fant jeg ut at et todelt
tastatur der tastene har parallelle kolonner passet meg best. Et todelt tastatur vil gi
større frihet i håndplassering, mens parallelle kolonner fremfor parallelle rader gir en
mer naturlig bevegelsesmønster for fingrene når tastaturet er i bruk.

For å realisere konseptet mitt trenger jeg nå å utvikle både maskinvare og fastvare.

## 1.4 Maskinvare

### 1.4.1 Design

Jeg gikk gjennom litt forskjellige design før jeg landet på et todelt tastatur med fem
rader og syv kolonner på hver. Den mengden taster har jeg sett vil gi meg alle knappene
jeg ønsker meg i tillegg til at det lar meg ha alle radene og alle kolonnene på hver sin
port perifer på mikrokontrollerene. AVR DU og DA er begge 8-bit mikrokontrollere noe
som betyr at de har 8-bits minneaddresser, og har derfor 8 pinner tilgjengelig for hver
GPIO port modul.

AVR64DU32 og AVR64DA32 ble valget av mikrokontrollere fordi jeg skulle ta i bruk
produkt utviklet av Microchip og den nye AVR DU mikrokontrolleren kommer med en
USB-modul som passer veldig bra ettersom kommunikasjon over USB med en PC er et
av kravene jeg må oppfylle. For høyresiden av tastaturet trengs ikke USBkommunikasjonsmuligheter og jeg har derfor benyttet meg av den litt eldre AVR DA
mikrokontrolleren som i de store trekkene er svært lik en AVR DU, men uten USBmodulen blir flere pinner frigjort til fremtidige utviklingsmuligheter.

USB-kommunikasjonen trenger nødvendigvis å skje gjennom en USB-kabel og for det
trenger jeg en USB-kontakt. Her valgte jeg å bruke den nyeste tilkoblingen, altså USB-C.
Etter opplesning på USB-standarden fant jeg de nødvendige koblingene for USBkontakten for at den skulle gi tastaturet det det trenger. For å få USB-kontakten til å
levere en stabil spenning på 5V til VBUS utgangen som er det vi ønsker oss, trenger en å
koble CC1 og CC2 pinnene til jord gjennom 5.1kOhm motstander.

For kommunikasjon mellom de to delene har jeg valgt å bruke I2C-protokollen. Dette er
en mye brukt standard i industrien og AVR mikrokontrollere har gode moduler som
gjør utviklingen med denne lettere. I tillegg støtter I2C opptil 1MHz
kommunikasjonshastighet som er mye raskere enn det som trengs her. Det viktigste
kriteriet til responstiden for tastaturet er at den ikke bør bemerkes av mennesket som
bruker det, og det er 1MHz mye mer enn godt nok for.

I2C-standarden er en kommunikasjonsprotokoll som benytter seg av to ledninger; med
en klokkelinje (SCL) og en datalinje (SDA). I tillegg trenger høyre del av tastaturet også
kraftforsyning, og det er naturlig å koble sammen samme sted som kommunikasjonen.
Derfor valgte jeg å bruke en fire-pols-aux-kabel for å koble de to delene sammen, med
VDD, jord, SCL og SDA på de fire ledningene.

For å realisere knappene er konseptet veldig enkelt. En bryter er koblet i serie med en
diode mellom hver kombinasjon av rad og kolonne. Hvordan dette vil la meg oppfatte
når alle de ulike knappene blir trykket kommer jeg tilbake til i større detalj i delen om
fastvare.

Jeg tok i bruk programmet KiCAD for å utvikle kretsdiagram. KiCAD kommer også med
store bibliotek av ferdiglagde symbol for ulike komponenter som gjør steget over til
implementasjon veldig smidig. Resultatet av tegningene av kretsdiagram kan sees i
Vedlegg B.

### 1.4.2 Implementasjon

For å implementere maskinvaren fortsatte jeg altså å benytte meg av KiCAD. KiCAD lar
en koble sammen symbolene man har brukt i kretsdiagramutviklingen til fotavtrykk av
faktiske komponenter og deretter plassere dem sammen og koble dem opp på et
kretskort, så mye var allerede gjort i designfasen. De største utfordringene i denne fasen
ble å finne fotavtrykk for komponenter som jeg hadde mulighet til å få tak i, samt å ta
gode valg av taster og dioder.

Når det kommer til tastevalg, er det to klare familier av taster med to ulike fotavtrykk
for kretskortet. Cherry MX taster har høyere profil og større bredde i trykkfølelse mens
Kailh taster har lavere profil. Jeg valgte å gå for Cherry MX Brown taster som er en taktil
tast, men som lager mindre lyd enn andre taktile taster, noe jeg hadde ønsket meg.

For diodene til hver tast valgte jeg å gå for 1N4148 dioder som er svært mye brukt
silikondiode som er svært lett tilgjengelig, billig og møter alle kravene vi måtte trenge.

For oppkobling av de to mikrokontrollene har jeg koblet USB-, I2C-konnektor til de
nødvendige pinnene og beholdt en port ledig på hver av dem til henholdsvis rader og
kolonner. Det er flere VDD og jord tilkoblinger på mikrokontrollorene og som anbefalt i
databladene deres er hvert VDD- og jordpar koblet sammen med en 100nF
kondensator. Utenom VUSB og jord på AVR DU, disse trenger en 470nF kondensator for
at den interne spenningsregulatoren skal kunne omgjøre 5V inngangsspenningen om til
3.3V spenningen USB-standarden bruker.

For at det skal være mulig å programmere mikrokontrollerene også etter de er loddet
fast i kretskortet har jeg dratt ut pinner for VDD, jord, UPDI og reset som er pinnene de
fleste Microchip debuggere trenger tilgang til for å kunne programmere en chip. I tillegg
har jeg valgt å inkludere en reset-krets for hver av mikrokontrollerene som er koblet
opp akkurat som anbefalt i databladene til chippene med en bryter i serie med en
resistor som begge er parallelkoblet til en kondensator. En reset-krets er en enkel måte
å få mikrokontrolleren ut av en eventuell frysning e.l. skulle det oppstå noen uventede
feil.

På det venstre kretskortet valgte jeg å legge til et potensiometer koblet til VDD og jord
med en inngang til en av mikrokontrollerens ADC innganger. I denne omgang har jeg
ikke tenkt å ta den i bruk, men i fremtiden ser jeg for meg å inkludere en del i fastvaren
som kan benytte seg av dette til å sende volumkontrollsignaler til PC.

Mens på høyre kretskort har jeg dratt ut de ubrukte pinnene til tilkoblingspinner så
disse er tilgjengelig for å slippe kreativiteten løs i fremtiden. Jeg ser for meg å f.eks.
bruke UART kommunikasjon til å kommunisere med en enkel LCD skjerm.

Tegninger av kretskortene jeg designet finner man under Vedlegg C, mens bilder av
ferdig loddet kretskort med alle delene på er under Vedlegg D.

## 1.5 Fastvare

### 1.5.1 Design

Til å begynne med tenkte jeg på hvordan jeg skulle implementere fastvarens viktigste
oppgave, nemlig å detektere ulike tastetrykk. Løsningen starter med å ha kolonnepinnene satt opp som input-pinner, mens rad-pinnene er satt opp som output-pinner.

Utfordringen kommer av at det ikke er nok pinner på mikrokontrolleren til å koble
sammen hvert par av kolonne og rad på ulike pinner, i stedet må man ha alle radene
koblet til en kolonne på samme pinne. Da oppstår problemet med at om en trykker ned
en tast vil kolonne-pinnen tasten er koblet til få beskjed om at den har gått f.eks. lav
men uten å kunne vite hvilken rad som trakk den lav.

Implementasjonen jeg har gått for fungerer slik: input-pinnene har en intern pull-up
motstand aktivert som forsikrer seg om at disse er på et høyt nivå når ingen rader er
koblet til dem. Til å starte med er også alle output-pinnene satt til å gi ut et høyt nivå, så
ingen tastetrykk vil kunne detekteres. Deretter starter PIT (Period Interrupt Timer)
modulen å gå dra én og én rad lav og om en oppdager at en kolonne blir dratt lav
sjekker man hvilken rad som på det tidspunktet er konfigurert lav og på den måten vet
man hvilket par og dermed hvilken knapp som er aktivert. Denne løsningen er basert på
Egil Rotevatn sin løsning for sitt egenutviklede tastatur «Splitbird».

I tillegg skal fastvaren håndtere kommunikasjon, både over USB til PC og over I2C
mellom de to delene. For dette tar jeg i bruk TWI (Two-Wire Interface) modulen som
finnes på både AVR DU og DA som er I2C kompatibel, og for USB-kommunikasjonen tar
jeg i bruk USB-modulen på AVR DU. For å lese hvordan disse fungerer i større detalj kan
en sjekke AVR DU og DA databladene og lese USB 2.0 spesifikasjonen, og I2C-bussspesifikasjonen som alle ligger i referanselisten.

### 1.5.2 Implementasjon

For løsningen av implementasjon av fastvaren tenkte jeg i utgangspunktet å bruke Egil
Rotevatn sin kildekode som et startpunkt ettersom det var hans løsning jeg baserte meg
på for detektering av tastetrykk, men jeg endte opp med å bruke svært lite kode derfra
og valgte heller å skrive det litt mer fra bunnen av, både for å få bedre forståelse av
koden jeg bruker og fordi mye av Egils inkluderer elementer jeg ikke bruker.

Jeg har benyttet meg av Microchip Studio for å skrive koden. Dette er et integrert
utviklingsmiljø spesielt laget for utvikling av fastvare for AVR mikrokontrollere.
For å se implementasjonsløsningen min i større detalj kan en sjekke ut GitHub depotet
under Vedlegg A, der ligger fastvarekoden under /firmware. Koden under
/firmware/usb er kode utgitt av Microchip bruk med USB-modulen.

Her holder jeg fortsatt på å utvikle mer av funksjonaliteten jeg ønsker, så GitHub
depotet vil nok utvikle seg videre, også i dagene etter denne rapporten er levert. Mens
jeg skriver dette er ikke TWI-modulen altså I2C-kommunikasjonen oppe og kjøre.

# 3 Verifikasjon og testing

## 1.6 Kretstesting

For testing av kretskort og lodding har jeg utført litt standard in-circuit testing. Har
sjekket for kortslutninger. Sjekket at spenningsnivået på VDD er tilnærmet 5V når USBkonnektoren er tilkoblet. Testet for defekte pinner på kontrolleren. Sjekket at
kapasitans- og motstandsverdiene stemmer. Her ser alt ut til å stemme.

## 1.7 Fastvaretesting

For fastvaretesting har jeg benyttet meg av testing underveis som jeg har utviklet nye
deler av fastvaren. Ved å teste at et og et nytt tillegg til koden fungerer som det skal blir
det mye lettere å oppdage hvor feilene ligger.

Jeg har god kjennskap til USART modulen på AVR kontrollere fra før så her har jeg
benyttet meg av denne for å gi meg rask tilbakemelding på om koden jeg skriver
fungerer som den skal. USART lar meg sende beskjeder fra mikrokontrolleren til en PC
og lese dem ut med verktøy som PuTTY. I tillegg kommer de fleste modulene på
mikrokontrollerene med tonnevis av statusbits jeg kan lese ut for å få et innblikk i hvor
feil ligger.

I tillegg kommer Microchip studio med veldig praktiske feilsøkingsverktøy til å lese ut
registerverdier og se løpet til koden et steg av gangen som lar meg teste koden der jeg
ønsker og se at alt skjer som forventet.
Her har jeg ikke kommet helt i mål enda og holder fortsatt på å utvikle noe av
funksjonaliteten.

# 4 Konklusjon

For å konkludere har jeg skapt et egenutviklet tastatur der maskinvare og fastvare er
designet av meg etter mine egne ønsker. Tastaturet har utforming og funksjonalitet for
å sikre god komfort og fornøyelse når jeg bruker det. Det tar i bruk to stykk AVR
mikrokontrollere og kommuniserer med PC ved bruk av USB-standarden. Alt etter
spesifikasjonen.

Fortsatt gjenstår å knytte de to delene sammen ved bruk av I2C så tastaturet kan forenes
i ett enkelt fungerende tastatur. Og i tillegg er det lagt opp til muligheten for fremtidige
utvidelsesprosjekter til tastaturet. Jeg har også en plan om å 3D-modellere en case til
tastaturet.

# Referanser
 - Microchip Technology Inc. (2020, March). AVR128DA28/32/48/64 Preliminary Data
Sheet. Retrieved from Microchip:
https://ww1.microchip.com/downloads/en/DeviceDoc/40002183A.pdf
- Microchip Technology Inc. (2024). AVR64DU28/32 Preliminary Data Sheet. Retrieved
from Microchip:
https://ww1.microchip.com/downloads/aemDocuments/documents/MCU08/P
roductDocuments/DataSheets/AVR64DU-28-32-Prelim-DataSheetDS40002548.pdf
- NXP Semiconductors. (2021, October 1). I2C-bus specification and user manual.
Retrieved from NXP: https://www.nxp.com/docs/en/user-guide/UM10204.pdf
- Rotevatn, E. (2023, April 21). SplitBird Keyboard. Retrieved from GitLab:
https://gitlab.com/printedcircuitbirds/splitbird
- USB Implementers Forum. (2024, September 27). USB 2.0 Specification. Retrieved from
USB: https://www.usb.org/document-library/usb-20-specification
- USB Implementers Forum. (2024, October 28). USB Type-C® Cable and Connector
Specification Release 2.4. Retrieved from USB: https://www.usb.org/documentlibrary/usb-type-cr-cable-and-connector-specification-release-24

# Vedlegg A

## GitHub-depot

Fastvarekoden, KiCAD-prosjekter (kretsdiagram- og kretskortfiler) og mulighet til å
følge med på og delta i videre utvikling kan finnes på
https://github.com/AndersKristof/keyboard. Dette er det ideelle startpunktet om en
ønsker å bygge eller videreutvikle tastaturet selv.

# Vedlegg B

## Tegninger av kretsdiagram

![Kretsdiagram for venstre del](/images/circuit-diagram-left.png)

![Kretsdiagram for høyre del](/images/circuit-diagram-right.png)

# Vedlegg C

## Tegninger av kretskort

![Kretskort for venstre del](/images/pcb-diagram-left.svg)

![Kretskort for høyre del](/images/pcb-diagram-right.svg)

# Vedlegg D

## Bilder av ferdig loddet tastatur

![Bilde av ferdig produkt for venstre del](/images/finished-product-left.jpg)

![Kretsdiagram for høyre del](/images/finished-product-right.jpg)

