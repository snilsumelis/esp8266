# esp8266
# ESP8266 WiFi Modülü Kontrolü

Bu kod bloğu, Texas Instruments Tiva C Series TM4C1294XL mikrodenetleyici kartı ve ESP8266 WiFi modülü arasında seri iletişim kullanarak kontrol sağlar. Kod bloğu, ESP8266 modülü üzerinden AT komutlarını kullanarak WiFi ayarlarını yapılandırır ve bir WiFi Erişim Noktası (Access Point - AP) oluşturur.

## Kod Açıklaması

Bu kod, Tiva C Series TM4C1294XL mikrodenetleyici kartı ve ESP8266 WiFi modülünün seri iletişim arayüzünü kullanarak aşağıdaki işlevleri gerçekleştirir:

- ESP8266 modülünü başlatır ve durumunu izler.
- Echo modunu kapatır.
- WiFi modunu ayarlar.
- Birden fazla bağlantıya izin verme seçeneğini ayarlar.
- Bir WiFi Erişim Noktası (AP) oluşturur ve ayarlarını yapılandırır.
- Bir sunucu başlatır ve belirtilen bir bağlantı noktasında bağlantıları kabul eder.
- Döngüde, her saniye USB üzerinden "merhaba" mesajı gönderir.

Bu kod, seri iletişim aracılığıyla ESP8266 modülünün AT komutlarını kullanarak WiFi ayarlarını yapılandırır ve bir AP oluşturur.

## Kullanılan Donanım ve Kütüphaneler
- Texas Instruments Tiva C Series TM4C1294XL mikrodenetleyici kartı
- ESP8266 WiFi modülü
- TI-RTOS (TI Gerçek Zamanlı İşletim Sistemi)
- TivaWare Kütüphanesi
- TI-DRIVERS Kütüphanesi


