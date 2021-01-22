#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#define PIN 26
#define NUMPIXELS 300

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_RGB + NEO_KHZ800);

void setup() {
  Serial.begin(9600);
  Serial.println("Hallo Ich bin Moritz' super Programm höhö");
  pixels.begin();
}

void rocket(int hight, int r, int g, int b) {
  float mySpeed = sqrt(hight * 20);
  int pixel = 0;

  for (int t = 0; pixel < hight - 1; t++) {
    pixels.setPixelColor(pixel, pixels.Color(0, 0, 0));
    pixels.setPixelColor(pixel + 1, pixels.Color(0, 0, 0));
    pixels.setPixelColor(pixel + 2, pixels.Color(0, 0, 0));
    float seconds = t * 0.025;
    pixel = (mySpeed * seconds - 5 * seconds * seconds);
    pixels.setPixelColor(pixel, pixels.Color(r, g, b));
    pixels.setPixelColor(pixel + 1, pixels.Color(r, g, b));
    pixels.setPixelColor(pixel + 2, pixels.Color(r, g, b));
    pixels.show();
  }

  pixels.setPixelColor(pixel, pixels.Color(0, 0, 0));
  pixels.setPixelColor(pixel + 1, pixels.Color(0, 0, 0));
  pixels.setPixelColor(pixel + 2, pixels.Color(0, 0, 0));
  pixels.show();
}

void explosion(int firstHight, int secondHight, int numberOfParticles, int maxParticleSize, int r, int g, int b, int accelaration) {

  int hight = secondHight - firstHight;
  float mySpeed = sqrt(hight * 2 * accelaration);
  int pixel = 0;
  int upperParticle = 0;
  int lowerParticle = 0;
  int particleFactors[numberOfParticles];
  int particleSize[numberOfParticles];

  for (int i = 0; i < numberOfParticles; i++) {
    particleFactors[i] = random(1, 99);
    particleSize[i] = random(2, maxParticleSize);
  }

  for (int t = 0; pixel < secondHight - 1; t++) {
    pixels.setPixelColor(pixel, pixels.Color(0, 0, 0));
    for (int n = 0; n < numberOfParticles; n++) {
      upperParticle = (pixel - firstHight) * particleFactors[n] * 0.01 + firstHight;
      lowerParticle = firstHight - (upperParticle - firstHight);
      for (int x = 0; x < particleSize[n]; x++) {
        pixels.setPixelColor(upperParticle + x, pixels.Color(0, 0, 0));
        pixels.setPixelColor(lowerParticle - x, pixels.Color(0, 0, 0));
      }
    }

    float seconds = t * 0.05;  //higher factor increases the speed

    pixel = (mySpeed * seconds - accelaration * 0.5 * seconds * seconds) + firstHight;
    pixels.setPixelColor(pixel, pixels.Color(r, g, b));
    for (int n = 0; n < numberOfParticles; n++) {
      upperParticle = (pixel - firstHight) * particleFactors[n] * 0.01 + firstHight;
      lowerParticle = firstHight - (upperParticle - firstHight);
      for (int x = 0; x < particleSize[n]; x++) {
        pixels.setPixelColor(upperParticle + x, pixels.Color(r, g, b));
        pixels.setPixelColor(lowerParticle - x, pixels.Color(r, g, b));
      }
    }
    pixels.show();
  }
  delay(100);
  float upperParticleFactors[numberOfParticles];
  float lowerParticleFactors[numberOfParticles];
  for (int i = 0; i < numberOfParticles; i++) {
    upperParticleFactors[i] = (firstHight + particleFactors[i] * 0.01 * (secondHight - firstHight)) / secondHight;
    lowerParticleFactors[i] = (firstHight - particleFactors[i] * 0.01 * (secondHight - firstHight)) / secondHight;
  }

  for (int t = 0; pixel > 0; t++) {
    float seconds = t * 0.05;  //higher factor increases the speed
    pixels.setPixelColor(pixel, pixels.Color(0,0,0));
    for (int i = 0; i < numberOfParticles; i++) {
      upperParticle = pixel*upperParticleFactors[i];
      lowerParticle = pixel*lowerParticleFactors[i];
      for (int x = 0; x < particleSize[i]; x++) {
        pixels.setPixelColor(upperParticle + x, pixels.Color(0,0,0));
        pixels.setPixelColor(lowerParticle + x, pixels.Color(0,0,0));
      }
    }
    pixel = secondHight - 1.4 * seconds * seconds;
    pixels.setPixelColor(pixel, pixels.Color(r, g, b));
    for (int i = 0; i < numberOfParticles; i++) {
      upperParticle = pixel*upperParticleFactors[i];
      lowerParticle = pixel*lowerParticleFactors[i];
      for (int x = 0; x < particleSize[i]; x++) {
        pixels.setPixelColor(upperParticle + x, pixels.Color(r, g, b));
        pixels.setPixelColor(lowerParticle + x, pixels.Color(r, g, b));
      }
    }
    pixels.show();
  }
  //uncomment to fade-out the particles
  /* while (r > 0 || g > 0 || b > 0) {
     if (r > 0) {
       r--;
     }
     if (g > 0) {
       g--;
     }
     if (b > 0) {
       b--;
     }
     pixels.setPixelColor(pixel, pixels.Color(r, g, b));
     for (int n = 0; n < numberOfParticles; n++) {
       upperParticle = (pixel - firstHight) * particleFactors[n] * 0.01 + firstHight;
       lowerParticle = firstHight-(upperParticle-firstHight);
       for (int x = 0; x < particleSize[n]; x++) {
         pixels.setPixelColor(upperParticle + x, pixels.Color(r, g, b));
         pixels.setPixelColor(lowerParticle - x, pixels.Color(r, g, b));
       }
     }
     pixels.show();
     delay(1); //fadespeed
    }*/
    pixels.setPixelColor(3, pixels.Color(0,0,0));
    pixels.setPixelColor(2, pixels.Color(0,0,0));
    pixels.setPixelColor(1, pixels.Color(0,0,0));
    pixels.setPixelColor(0, pixels.Color(0,0,0));
    pixels.show();
}

void loop() {
  int firstHight = random(40, 100);
  int secondHight = firstHight+random(30, 100);
  int numberOfParticals = random(4, 30);
  rocket(firstHight, 120, 120, 120);
  explosion(firstHight, secondHight, 20, 4, random(255), random(255), random(255), random(2,30));
  
  delay(500);
}
