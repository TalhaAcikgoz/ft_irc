#include "ft_irc.hpp"

int main() {
    // Soket oluşturma
    int soket = socket(AF_INET, SOCK_STREAM, 0);
    if (soket == -1) {
        std::cerr << "Soket oluşturulamadı." << std::endl;
        return 1;
    }

    // Soket adresi ayarlama
    sockaddr seradrr;
    seradrr.sa_family = AF_INET;
    seradrr.sa_data;
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
