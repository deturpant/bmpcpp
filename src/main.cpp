#include <iostream>
#include <limits>
#include "BMP/BMP.h"
#include "Menu/MyMenu.h"
#include "Menu/MenuItem.h"
#include "Exceptions/MyException.h"

#define SIZE_MENU 6

using namespace KVA;
void info(vector<any> params) {
    auto *bmp = any_cast<BMP*>(params[0]);
    std::cout << "Запущена функция показа информации о файле...\n";
    bmp->info();
}
void circ(vector<any> params) {
    auto *bmp = any_cast<BMP*>(params[0]);
    std::cout << "Запущена функция вырезания окружности...\n";
    bmp->createCircle();
    std::cout << "Окружность вырезана!\n";
}
void fills(vector<any> params) {
    int32_t x, y, w,h;
    uint8_t r,g,b;
    auto *bmp = any_cast<BMP*>(params[0]);
    std::cout << "Введите стартовую точку x: ";
    cin >> x;
    std::cout << "Введите стартовую точку y: ";
    cin >> y;
    std::cout << "Введите ширину заливки: ";
    cin >> w;
    std::cout << "Введите высоту заливки: ";
    cin >> h;
    std::cout << "Введите код красного цвета (R 0<=255): ";
    cin >> r;
    std::cout << "Введите код зеленого цвета (G 0<=255): ";
    cin >> g;
    std::cout << "Введите код синего цвета (B 0<=255): ";
    cin >> b;
    bmp->fillRegion(x,y,w,h,r,g,b,0);
    std::cout << "Область успешно залита!\n";
}
void scale(vector<any>params) {
auto *bmp = any_cast<BMP*>(params[0]);
    int32_t w,h;
    std::cout << "Введите ширину: ";
    cin >> w;
    std::cout << "Введите высоту: ";
    cin >> h;
    bmp->scale(w,h);
    cout << "Изображение успешно сжато!\n";
}
void saveFile(vector<any>params) {
    auto *bmp = any_cast<BMP*>(params[0]);
    std::string write_file = any_cast<string>(params[2]);
    cout << "Запущена функция сохранения файла...\n";
    bmp->save(write_file);
    cout << "Сохранение успешно выполнено в файл " << write_file << "\n";
}
void exitt(vector<any>params) {
    saveFile(params);
    cout << "Выход из программы...";
    exit(0);
}
void clearCIN() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.clear();
}
string MyException::file_name = "logs.txt";
int main(int argc, char *argv[]) {
    std::string load_data_file = "MARBLES.BMP";
    std::string write_data_file = "out.bmp";
    std::string log_data_file = "logs.txt";
    if (argc>=3) {
        load_data_file = argv[1];
        write_data_file = argv[2];
        log_data_file = argv[3];
    }
    KVA::MyException::setFileName(log_data_file);

    BMP *file = new BMP(load_data_file);
    MenuItem items[SIZE_MENU] = {
            MenuItem("Информация об открытом файле", info),
            MenuItem("Вырезать окружность из открытого файла", circ),
            MenuItem("Залить выбранную область цветом", fills),
            MenuItem("Сжать изображение до нужного расширения", scale),
            MenuItem("Сохранить файл", saveFile),
            MenuItem("Выход из программы", exitt)
    };
    MyMenu menu("BMP Programm", items, SIZE_MENU);
    vector<any> params {file, load_data_file, write_data_file};
    while (true) {
        try {
            menu.runCommand(params);
        }
        catch(const MyException &ex) {
            std::cout << "\nError: " << ex.getError() << "\n";
            clearCIN;
        }
    }
    return 0;
}
