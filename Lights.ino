/*static*/ void Lights::init() {
}

/*static*/ void Lights::poll() {
  static bool lightOn[deckCount] {};

  uint32_t daySeconds = g_now.unixtime() % DAY;
  for (int i=0; i<deckCount; i++) {
    const bool afterSunrise = daySeconds >= g_deckList[i].sunriseTime;
    const bool beforeSunset = daySeconds < (g_deckList[i].sunriseTime + g_deckList[i].lightDuration);
    const bool shouldBeOn = afterSunrise && beforeSunset;
    
    if (lightOn[i] != shouldBeOn) {
      lightOn[i] = shouldBeOn;
      Log::logString(Log::info, (shouldBeOn ? "Sunrise #" : "Sunset #") + String(g_deckList[i].id));
      setOutlet(g_deckList[i].lightOutlet, shouldBeOn);
    }
  }
}
