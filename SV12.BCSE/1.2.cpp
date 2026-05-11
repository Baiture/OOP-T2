class PointTest {
public:
    void testCase() {
        Point A(3, 4);
        std::cout << "A = ";
        A.print();

        Point B;
        B.read();
        std::cout << "B = ";
        B.print();

        Point C(-B.getX(), -B.getY());
        std::cout << "C = ";
        C.print();

        std::cout << "Khoang cach tu B den O: " << B.distance() << std::endl;

        std::cout << "Khoang cach tu A den B: " << A.distance(B) << std::endl;
    }
};
