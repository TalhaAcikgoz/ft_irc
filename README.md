# ft_irc
42 Project

work in progress

## FUNCTIONS

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


## Listen fonksiyonu kullanimi

`listen` fonksiyonu, bir soketi bağlantı taleplerini kabul etmeye hazır hale getirmek için kullanılır. Aşağıda `listen` fonksiyonunun imzası ve argümanları yer almaktadır:

```cpp
int listen(int sockfd, int backlog);
```

`listen` fonksiyonunun iki argümanı vardır:

1. **sockfd**: Dinlemeye alınacak soketin dosya tanıtıcısı (file descriptor) veya soketin kendisi. Bu, `socket` fonksiyonu tarafından döndürülen soketin dosya tanıtıcısıdır.

2. **backlog**: Bekleyen bağlantı sırasındaki bağlantı kuyruğunun maksimum uzunluğunu belirten bir tamsayı değeri. Bu, aynı anda kabul edilebilecek maksimum bağlantı sayısını belirtir. Talep edilen bağlantılar bu kuyrukta bekler. Bağlantıların taleplerini kabul etmek için `accept` fonksiyonu kullanılır.

`listen` fonksiyonu, başarı durumunda 0 değerini döndürür. Başarısızlık durumunda -1 döndürür ve `errno` değişkeni ayarlanır.

Örnek bir kullanım:

```cpp
if (listen(sock, 5) == -1) {
    std::cerr << "Soket dinlemeye başlanamadı." << std::endl;
    return 1;
}
```

Yukarıdaki örnekte, `listen` fonksiyonu `sock` soketini dinlemeye başlar ve maksimum 5 bağlantı talebini kuyrukta bekletebilir. Bu, aynı anda en fazla 5 bağlantı talebinin kabul edilebileceği anlamına gelir.

## Basit bir socket dinleme islemi

Soketi dinlemeye almak için aşağıdaki adımları izleyebilirsiniz:

1. Soket oluşturun: `socket` fonksiyonunu kullanarak bir soket oluşturun. İlgili adresleme alanı (`AF_INET` veya `AF_INET6`) ve soket türü (`SOCK_STREAM` veya `SOCK_DGRAM`) seçimini yapın.

2. Adres ve bağlantı noktası atanın: Oluşturulan sokete bir adres ve bağlantı noktası atayın. Bu, `bind` fonksiyonunu kullanarak yapılır. Adres, genellikle "localhost" veya kullanmak istediğiniz bir IP adresi olabilir ve bağlantı noktası belirli bir port numarasıdır.

3. Dinlemeye başlayın: Soketi dinlemeye başlamak için `listen` fonksiyonunu kullanın. Bu fonksiyon, gelen bağlantı taleplerini kabul etmeye ve uygun bağlantıları oluşturmak için beklemeye başlar.

Örnek bir C++ programında bu adımlar aşağıdaki gibi olabilir:

```cpp
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>

int main() {
    // Soket oluşturma
    int soket = socket(AF_INET, SOCK_STREAM, 0);
    if (soket == -1) {
        std::cerr << "Soket oluşturulamadı." << std::endl;
        return 1;
    }

    // Soket adresi ayarlama
    sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY); // Tüm yerel IP adreslerini kabul et
    serverAddress.sin_port = htons(12345); // Belirli bir bağlantı noktası

    // Soketi localhost ve belirli bir bağlantı noktasına bağlama
    if (bind(soket, reinterpret_cast<sockaddr*>(&serverAddress), sizeof(serverAddress)) == -1) {
        std::cerr << "Soket bağlanamadı." << std::endl;
        return 1;
    }

    // Soketi dinlemeye başlama
    if (listen(soket, 1) == -1) {
        std::cerr << "Soket dinlemeye başlanamadı." << std::endl;
        return 1;
    }

    std::cout << "Soket oluşturuldu ve dinleme başladı." << std::endl;

    // Soketi kapatma
    close(soket);

    return 0;
}
```

Yukarıdaki örnekte, soket oluşturulur, bir adres ve bağlantı noktası atanır ve soket dinlemeye başlar. Program, "Soket oluşturuldu ve dinleme başladı." mesajını gösterecektir. Bu noktadan itibaren soket, gelen bağlantı taleplerini kabul edebilir ve uygun işlemlerle devam edebilirsiniz.
