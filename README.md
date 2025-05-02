MiniSpotify - PROIECT 2 POO
Aceasta aplicatie este o versiune simplificata a unui serviciu de streaming muzical, similar Spotify.
Iata principalele functionalitati pe care le ofera utilizatorilor:

1. Functionalitati principale
    Biblioteca muzicala:
        - contine melodii organizate pe categorii: pop, rock si clasica
        - fiecare melodie are: titlu, artist, durata, gen si popularitate
        - melodiile sunt incarcate automat din fisierele text la pornire

    Playlist-uri:
        - utilizatorul poate crea playlist-uri personale
        - posibilitatea de a adauga/sterge melodii din playlist-uri
        - playlist-urile pot fi redate in intregime
        - exista playlist-uri predefinite la pornire

    Optiunea "Favorite":
        - utilizatorul poate adauga melodii la favorite
        - lista de melodii favorite poate fi vizualizata si redata
        - posibilitatea de a marca artisti preferati

    Istoric:
        - pastreaza o lista a ultimelor melodii redate
        - afiseaza de cate ori a fost redata fiecare melodie

    Cautare
        - cautare melodii dupa titlu sau artist
        - afisare rezultate si posibilitate de redare

2. Utilizare
    La pornire, aplicatia:
        - cere un nume de utilizator
        - incarca automat datele initiale (melodii si playlist-uri)
        - afiseaza un meniu principal cu optiuni

    Meniul principal ofera:
        - exploreaza biblioteca - vezi artisti, melodii populare
        - playlist-urile tale - gestioneaza playlist-uri
        - melodiile favorite - vezi si reda melodii favorite
        - istoric redari - vezi ce ai ascultat recent
        - cauta melodii - cauta dupa titlu sau artist

3. Tipuri de melodii
    Aplicatia "suporta" trei categorii principale de melodii:
        - pop - caracterizate prin energie (0-100%)
        - rock - cu variante normale si heavy
        - clasica - organizate pe epoci (Baroc, Romantism etc.)

Fiecare tip de melodie are un calcul specific al popularitatii, bazat pe:
        - numar de redari
        - caracteristici specifice genului (energie pentru pop, epoca pentru clasica etc.)

4. Managementul datelor
    Datele sunt incarcate din fisiere text la pornire
    Modificarile utilizatorului (playlist-uri, favorite) sunt salvate doar in memorie
    La inchiderea aplicatiei, modificarile se pierd (nu sunt persistate pe disk)
