


        temp.suma = 0;
        temp.pazymiai.clear();
        int paz;
        for (int i = 0; i < n; i++) { 
            iss >> paz;
            temp.suma += paz;
            temp.pazymiai.push_back(paz);
        }
        iss >> temp.egzam;
        temp.vidurkis = temp.suma/temp.pazymiai.size();
        mediana_skaiciavimas(temp.pazymiai, temp.pazymiai.size(), temp);
        temp.gal_vid = 0.4 * temp.vidurkis + 0.6 * temp.egzam;
        temp.gal_med = 0.4 * temp.mediana + 0.6 * temp.egzam;
        grupe.push_back(temp);