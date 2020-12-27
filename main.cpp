#include "classes.hpp"
#include <thread>
#include <functional>

typedef int TP;

void help();

class Myclass{

    int bufsize = 0;
    int place = 0;
    int nowcount = 0;
    char filename[256];

    Factory<TP>* vec;



std::function<void()> f[3] = {[&]() {
                                      //printf("\t 4 - создание фигуры\n ");
                                      int fig = 0;
                                      TP xl, yl, xr, yr;
                                      std::cout << "Введите номер добавляемой фигуры:\n1 - Треугольник\n2 - Прямоугольник\n3 - Квадрат" << endl;
                                      cin >> fig;
                                      switch (fig)
                                      {
                                      case 1:
                                      {
                                          std::cout << "Введите координаты фигуры в направлении против часовой стрелки\n"
                                                    << endl;
                                          std::cin >> xl >> yl >> xr >> yr;
                                          Triangle<TP> a(xl, yl, xr, yr);
                                          vec[place % bufsize] = a;
                                          std::cout << "Элемент вставлен." << endl;
                                          break;
                                      }
                                      case 2:
                                      {
                                          std::cout << "Введите координаты диагональных вершин фигуры\n"
                                                    << endl;
                                          std::cin >> xl >> yl >> xr >> yr;
                                          Rectangle<TP> a(xl, yl, xr, yr);
                                          vec[place % bufsize] = a;
                                          std::cout << "Элемент вставлен." << endl;
                                          break;
                                      }
                                      case 3:
                                      {
                                          std::cout << "Введите координаты диагональных вершин фигуры\n"
                                                    << endl;
                                          std::cin >> xl >> yl >> xr >> yr;
                                          Square<TP> a(xl, yl, xr, yr);
                                          vec[place % bufsize] = a;
                                          std::cout << "Элемент вставлен." << endl;
                                          break;
                                      }
                                      default:
                                          printf("Введённый номер не соответствует фигуре\n Продолжить?\n");
                                          help();
                                          return;
                                      }
                                      ++place;
                                      ++nowcount;

                                      return;
                                  },
                                  [&]() { //вывод на экран
                                      if (nowcount == 0)
                                      {
                                          printf("Фигур нет.\n");
                                          return;
                                      }
                                      for (int i = 0; i < nowcount; i++)
                                      {
                                          printf("Фигура №%d\n", i + 1);
                                          Factory<TP> figure = vec[i];
                                          for (int i = 0; i < figure.count; i++)
                                          {
                                              printf("Вершина №%d: ", i + 1);
                                              cout << figure.a[i].first << " " << figure.a[i].second << endl;
                                          }
                                      }
                                      return;
                                  },
                                  [&]() { //вывод в файл
                                      if (nowcount == 0)
                                      {
                                          printf("Фигур нет.\n");
                                          return;
                                      }

                                      FILE *fl = fopen(filename, "a+");

                                      for (int i = 0; i < nowcount; i++)
                                      {
                                          fprintf(fl, "Фигура №%d\n", i + 1);
                                          Factory<TP> figure = vec[i];
                                          for (int i = 0; i < figure.count; i++)
                                          {
                                              fprintf(fl, "Вершина №%d: %d %d\n", i + 1, figure.a[i].first, figure.a[i].second);
                                          }
                                      }
                                      fprintf(fl,"\n");
                                      fclose(fl);
                                      return;
                                  }};

void Clear(){
    delete [] this->vec;
    nowcount = 0;
    this->vec = new Factory<TP>[this->bufsize];
    this->place = 0;
}

void Print(){
    thread t(f[2]);
    f[1]();
    t.join();
    this->Clear();
}

public:

Myclass(){
    char file[] = "outMyclass.txt";
    int n = 0;
    while(file[n] != '\0'){
        filename[n] = file[n];
        ++n;
    }
    
    
    bufsize = 1;
    delete vec;
    vec = new Factory<TP>;
}

Myclass(int s, char file[256]){
    int n = 0;
    while(file[n] != '\0'){
        filename[n] = file[n];
        ++n;
    }
    bufsize = s;
    delete vec;
    vec = new Factory<TP>[s];
}

Myclass(Myclass &m){
    int n = 0;
    while(m.filename[n] != '\0'){
        filename[n] = m.filename[n];
        ++n;
    }
    this->bufsize = m.bufsize;
    if(this->bufsize > 1){
        delete [] this->vec;
    }else{
        delete this->vec;
    }
    this->vec = m.vec;
}

~Myclass(){
    printf("Фигуры, которые остались в контейнере:\n");
    this->Print();
    delete [] vec;
}

void Push(){
    f[0]();
    if(this->nowcount == bufsize){
        this->Print();
        printf("Буффер заполнился, поэтому он выведен в файл и опустошён\n");
    }
}




};


void help(){
    printf("Для выполнения операции введите соответствующую цифру:\n ");
    printf("\t 1 - Продолжить ввод значений\n ");
    printf("\t 0 - Выход\n ");
}


int main(int argc, char **argv)
{
    char enter = -1;
   
    int i = 0;
    if (argc < 2)
    {
        printf("Too few args\n");
        return 1;
    }
    int bufsize = 0;
    while (argv[1][i] != '\0')
    {
        bufsize += argv[1][i] - 48;
        bufsize *= 10;
        ++i;
    }
    bufsize /= 10;

    char filename[256];

    cout << "Введите имя файла для вывода буффера." << endl;
    fflush(stdin);
    cin >> filename;
    cout <<filename;
    //fgets(filename, sizeof(filename), stdin);
    fflush(stdin);
    
    Myclass mass(bufsize, filename);

    
    

    

    ///////////////////////////////////////////////////////////////////////////////main////////////////////////////////////////

    while((isdigit(enter))||enter == -1){
        mass.Push();
        enter = '0';
        cin>>enter;
        while(enter != '1'){
            if(enter == '0'){
                printf("Выход...\n");
            return 0;
        }else{
            if(enter != '1'){
            help();
            cin>>enter;
        }
        }
        }
    }

    printf("Похоже вы ввели не цифру\n Выход из программы...\n");
  

    return 0;
}