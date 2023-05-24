#include "Arduino.h"
#include "WiFi.h"
#include "Audio.h"
#include "SD.h"
#include "FS.h"

// Digital I/O used
#define I2S_DOUT      25
#define I2S_BCLK      27
#define I2S_LRC       26

Audio audio;

String ssid =     "shack";
String password = "welcome2shack";

void setup() {
    Serial.begin(115200);
    WiFi.disconnect();
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid.c_str(), password.c_str());
    while (WiFi.status() != WL_CONNECTED) delay(1500);
    audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
    audio.setVolume(5); // default 0...21
//  or alternative
//  audio.setVolumeSteps(64); // max 255
//  audio.setVolume(63);    
//
//  *** radio streams ***
    audio.connecttohost("http://radio.lassul.us/music.mp3");
    //audio.connecttohost("http://stream.antennethueringen.de/live/aac-64/stream.antennethueringen.de/");
    rotaryEncoder.begin();
    rotaryEncoder.setup(readEncoderISR);
    rotaryEncoder.setBoundaries(0, 21, false); //minValue, maxValue, circleValues true|false (when max go to min and vice versa)
    rotaryEncoder.disableAcceleration();
}

void loop()
{
    audio.loop();
    rotary_loop();

}
void rotary_loop()
{
  //dont do anything unless value changed
  if (rotaryEncoder.encoderChanged())
  {
    uint16_t v = rotaryEncoder.readEncoder();
    audio.setVolume(v);
    Serial.print("Volume %s"
  }
  //react on rotary encoder switch
  if (rotaryEncoder.isEncoderButtonClicked())
  {
    // TODO
  }
}

// optional
void audio_info(const char *info){
    Serial.print("info        "); Serial.println(info);
}
void audio_id3data(const char *info){  //id3 metadata
    Serial.print("id3data     ");Serial.println(info);
}
void audio_eof_mp3(const char *info){  //end of file
    Serial.print("eof_mp3     ");Serial.println(info);
}
void audio_showstation(const char *info){
    Serial.print("station     ");Serial.println(info);
}
void audio_showstreamtitle(const char *info){
    Serial.print("streamtitle ");Serial.println(info);
}
void audio_bitrate(const char *info){
    Serial.print("bitrate     ");Serial.println(info);
}
void audio_commercial(const char *info){  //duration in sec
    Serial.print("commercial  ");Serial.println(info);
}
void audio_icyurl(const char *info){  //homepage
    Serial.print("icyurl      ");Serial.println(info);
}
void audio_lasthost(const char *info){  //stream URL played
    Serial.print("lasthost    ");Serial.println(info);
}
void audio_eof_speech(const char *info){
    Serial.print("eof_speech  ");Serial.println(info);
}
