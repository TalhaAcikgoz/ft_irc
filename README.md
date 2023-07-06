# ft_irc
42 Project

## FUNCTION

1. **socket**: Bir soket oluşturur ve iletişim için kullanılacak bir dosya tanıtıcısı döndürür.
2. **close**: Bir soketi kapatır ve kullanılan kaynakları serbest bırakır.
3. **setsockopt**: Bir soketin seçeneklerini ayarlar.
4. **getsockname**: Bir soketin yerel adresini döndürür.
5. **getprotobyname**: Protokol ismine karşılık gelen protokol numarasını döndürür.
6. **gethostbyname**: Bir ana bilgisayar adına karşılık gelen IP adresini döndürür.
7. **getaddrinfo**: Bir hedef ad ve servis için bağlantı noktası bilgilerini döndürür.
8. **freeaddrinfo**: getaddrinfo işlevi tarafından oluşturulan adres bilgilerini serbest bırakır.
9. **bind**: Bir soketi belirtilen adres ve bağlantı noktasına bağlar.
10. **connect**: Bir soketi belirtilen hedefe bağlar.
11. **listen**: Bir soketi gelen bağlantı talepleri için dinlemeye başlar.
12. **accept**: Bağlantı taleplerini kabul eder ve yeni bir soket oluşturur.
13. **htons**: 16 bitlik bir değeri ağ bayt sırasına dönüştürür.
14. **htonl**: 32 bitlik bir değeri ağ bayt sırasına dönüştürür.
15. **ntohs**: 16 bitlik bir değeri ana makine bayt sırasına dönüştürür.
16. **ntohl**: 32 bitlik bir değeri ana makine bayt sırasına dönüştürür.
17. **inet_addr**: IP adresini, IPv4 adresinin ikili formuna dönüştürür.
18. **inet_ntoa**: IPv4 adresinin ikili formunu IP adresine dönüştürür.
19. **send**: Bir soketten veri gönderir.
20. **recv**: Bir soketten veri alır.
21. **signal**: Bir sinyal işleyici atanmasını sağlar.
22. **lseek**: Dosya konum göstergesini ayarlar.
23. **fstat**: Bir dosyanın durum bilgilerini alır.
24. **fcntl**: Dosya tanıtıcısının özelliklerini değiştirir.
25. **poll**: Bir dizi dosya tanıtıcısını dinler ve olayları bekler.


## Socket Fonksiyonu ve Kullanimi

C++'da `socket` fonksiyonu, soket oluşturmak için kullanılır ve aşağıdaki şekliyle tanımlanır:

```cpp
int socket(int domain, int type, int protocol);
```

`socket` fonksiyonunun üç argümanı vardır:

1. **domain**: Soketin kullanacağı adresleme alanını belirtir. Örnek olarak:
   - `AF_INET`: IPv4 adresleme alanı.
   - `AF_INET6`: IPv6 adresleme alanı.
   - `AF_UNIX` veya `AF_LOCAL`: Unix etki alanı soketleri.

2. **type**: Soketin türünü belirtir. Örnek olarak:
   - `SOCK_STREAM`: İkiden çok nokta arasında güvenilir, bağlantı temelli bir soket (TCP).
   - `SOCK_DGRAM`: İkiden çok nokta arasında güvenilmeyen, bağlantısız bir soket (UDP).

3. **protocol**: Soketin kullanacağı protokolü belirtir. Genellikle 0 olarak belirtilir, bu durumda `socket` fonksiyonu, `type` parametresine bağlı olarak uygun protokolü seçer. Ancak, belirli bir protokol kullanmak istiyorsanız, uygun protokol numarasını belirtmelisiniz. Örneğin:
   - `IPPROTO_TCP`: TCP protokolü.
   - `IPPROTO_UDP`: UDP protokolü.

`socket` fonksiyonu, başarılı olursa oluşturulan soketin dosya tanıtıcısını (file descriptor) döndürür. Başarısızlık durumunda -1 döndürür.

Örnek kullanımlar:
```cpp
int tcpSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); // TCP soketi oluşturur
int udpSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP); // UDP soketi oluşturur
```

Yukarıdaki örneklerde, `AF_INET` adresleme alanında çalışan TCP ve UDP soketleri oluşturulmaktadır.
