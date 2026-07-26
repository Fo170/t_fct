// t_fct : Temp de fonctionnement en secondes
// https://github.com/Fo170/t_fct

float t_fct;
unsigned long t0_fct;


// calcule du temps de fonctionnement
void INIT_Temp_fct(void)
{
 t0_fct = millis();	
}

void Calcule_Temp_fct(void) // Temp de fonctionnement en secondes
{
 t_fct = 0.001 * (float)(millis() - t0_fct); 
}

//============================================================
// FONCTION : Heure de mise en route (boot time)
//============================================================
// Retourne l'heure de démarrage calculée : Heure NTP actuelle - t_fct
//============================================================
// --- NTP : configuration France ---
const char* ntpServer = "fr.pool.ntp.org";
const long  gmtOffset_sec = 3600;       // UTC+1 (CET / heure d'hiver)
const int   daylightOffset_sec = 3600;  // +1h pour l'heure d'été (CEST)

time_t getBootTimeEpoch()
{
  time_t now_ntp = time(nullptr);
  if (now_ntp < 1000000000) return 0;               // NTP pas encore sync
  return now_ntp - (time_t)(t_fct + 0.5f);          // arrondi à la seconde
}

String getBootTimeString()
{
  time_t bootEpoch = getBootTimeEpoch();
  if (bootEpoch == 0) return String("NTP non synchronisé");

  struct tm *btm = localtime(&bootEpoch);
  char buf[30];
  // Format : JJ/MM/AAAA HH:MM:SS
  snprintf(buf, sizeof(buf), "%02d/%02d/%04d %02d:%02d:%02d",
           btm->tm_mday, btm->tm_mon + 1, btm->tm_year + 1900,
           btm->tm_hour, btm->tm_min, btm->tm_sec);
  return String(buf);
}