#include <iostream>
#include <math.h>

double teylorCos2(double x, double epsilon);

int main()
{
    double res = teylorCos2(1000000000., 1e-5);
    std::cout << "result:" << res << std::endl;
    std::cout << "cos(1000000000):" << cos(1000000000) << std::endl;

    const double res1 = teylorCos2(-1., 1e-5);
    std::cout << "result:" << res1 << std::endl;
    std::cout << "cos(-1):" << cos(-1);
    std::cout << std::endl;

    res = teylorCos2(2., 1e-5);
    std::cout << "result:" << res << std::endl;
    std::cout << "cos(2):" << cos(2);
    std::cout << std::endl;

    res = teylorCos2(100., 1e-5);
    std::cout << "result:" << res << std::endl;
    std::cout << "cos(100):" << cos(100);
    std::cout << std::endl;

    res = teylorCos2(-5., 1e-5);
    std::cout << "result:" << res << std::endl;
    std::cout << "cos(-5):" << cos(-5);
    std::cout << std::endl;

    res = teylorCos2(-1., 1e-5);
    std::cout << "result:" << res << std::endl;
    std::cout << "cos(-1):" << cos(-1);
    std::cout << std::endl;
}


double teylorCos2(double x, double epsilon)
{
    double res = 0;
    int buf = 0;

    __asm {
        //инициализируем стек
        finit  

        fldpi 

        fadd st(0), st(0) 
        fld qword ptr x 

        fdiv st(0), st(1) 

        fstcw word ptr buf
        mov  bx, word ptr buf
        or word ptr buf, 0x400
        fldcw word ptr buf

        frndint 

        fmul st(0), st(1)   
        fld qword ptr x  
        fsub st(0), st(1) 
        fxch st(2)  

        fstp st(0) 
        fstp st(0) 

        fmul st(0), st(0) //x^2 в 3          
        fld qword ptr epsilon //эпсилон в 4
        fxch st(1)
        fldz                //counter i = 0.0 in 2

        fld1                //sum in 1
        fld1                //Xi in 0

        COS_COUNTER :
        fchs                //меняем знак в st(0)
            fmul st(0), st(3)   //-Xi * x^2
            fld1                //единица в вершину
            faddp st(3), st(0)  //i++
            fdiv st(0), st(2)   //(-Xi * x^2)/i
            fld1                //единица в вершину
            faddp st(3), st(0)  //i++
            fdiv st(0), st(2)   //(-Xi * x^2)/i

            fadd st(1), st(0)   //sum += Xi

            fld st(0)           //st(0) = Xi
            fabs                //модуль st(0)
            fcomp st(5)         //Xi == eps? 

            
            fstsw ax            
            sahf
            // Xi > eps ->  выполняем снова
            ja COS_COUNTER
            // иначе
            fld st(1) //s(0) = sum
            fstp[res] // сохраняем результат
    }
    return res;
}