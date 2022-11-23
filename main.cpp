#include <iostream>
#include <cassert>
#include "BigInt.h"
#include <bitset>

//////////////////////////////////////////////////////////////////////////////////
/*TESTS*/
//////////////////////////////////////////////////////////////////////////////////

int main() {
    BigInt x = BigInt(55);
    BigInt y = BigInt(-543);
    x *= y;
    assert(x == BigInt(-29865));
    BigInt z(-200);
    x -= z;
    assert(x == BigInt(-29665));
    BigInt f(100);
    f /= BigInt(20);
    assert(f == BigInt(5));
    BigInt g(-100);

    assert(-g == BigInt(100));
    assert(g < BigInt(30));
    assert(g < BigInt(-200));
    // new tests
    BigInt a = BigInt("11244432343242");
    BigInt b = BigInt("45234483");
    BigInt c = a + b;
    assert(c == BigInt("11244477577725"));
    BigInt d = a - b;
    assert(d == BigInt("11244387108759"));
    BigInt e = a * b;


    BigInt q("12343");
    BigInt w("12343");
    BigInt r = q * w;
    assert(r == BigInt("152349649"));

    BigInt t("-12343");
    BigInt u("12343");
    BigInt i = t * u;
    assert(i == BigInt("-152349649"));

    BigInt o("12343");
    BigInt p("-1234334");
    BigInt s = o * p;
    assert(s == BigInt("-15235384562"));

    BigInt h("-654893");
    BigInt j("-96649");
    BigInt k = h * j;
    assert(k == BigInt("63294753557"));

    BigInt l("584275893247583247580342750892");
    BigInt m("58734075803428579230");
    BigInt n = l * m;
    assert(n == BigInt("34316904604119498822372378891221156525589375173160"));

    BigInt v("123456789012345678901234567890");
    BigInt b1("123456789012345678901234567890");
    BigInt b2 = v - b1;
    assert(b2 == BigInt("0"));

    BigInt b3("90");
    BigInt b4("91");
    BigInt b5 = b3 - b4;
    assert(b5 == BigInt("-1"));

    BigInt b6("123456789012345678901234567890");
    BigInt b7("123456789012345678901234567889");
    BigInt b8 = b6 - b7;
    assert(b8 == BigInt("1"));

    BigInt b9("123457890");
    BigInt b10("57837938489");
    BigInt b11 = b9 - b10;
    assert(b11 == BigInt("-57714480599"));
    assert(b11 < BigInt("0"));
    assert(-b11 == BigInt("57714480599"));

    BigInt b12("944387509324857349826755");
    BigInt b13("10");
    BigInt b14 = b12 % b13;
    assert(b14 == BigInt("5"));

    BigInt b15("944387509324857349826755");
    BigInt b16("5");
    BigInt b17 = b15 % b16;
    assert(b17 == BigInt("0"));

    BigInt b18("944387509324857349826755");
    BigInt b19("5");
    BigInt b20 = b18 / b19;
    assert(b20 == BigInt("188877501864971469965351"));

    BigInt b21("-944387509324857349826755");
    BigInt b22("5");
    BigInt b23 = b21 / b22;
    assert(b23 == BigInt("-188877501864971469965351"));

    BigInt b24("17561");
    BigInt b25("-1868709163");
    BigInt b26 = b24 + b25;
    assert(b26 == BigInt("-1868691602"));

    BigInt b27("8341");
    BigInt b28("-1283328947");
    BigInt b29 = b27 - b28;
    assert(b29 == BigInt("1283337288"));
    BigInt b30("110");
    BigInt b31("25");
    BigInt b32 = b30 % b31;
    assert(b32 == BigInt("10"));
    BigInt b33("-15");
    BigInt b34("7");
    BigInt b35 = b33 / b34;
    assert(b35 == BigInt("-2"));
    b35 *= b34;
    BigInt b36("-15");
    BigInt b37("7");
    BigInt b38 = b36 % b37;
    b35 += b38;
    assert(b35 == BigInt("-15"));

    BigInt b39("200");
    b39++;
    assert(b39 == BigInt("201"));

    BigInt b40("12312312312312");
    BigInt b41("12");
    BigInt b42 = b40 & b41;
    //BigInt b43("8");
    assert(b42 == BigInt("8"));


    BigInt b43("136457");
    BigInt b99("12938014");
    BigInt b45 = b43 | b99;
    BigInt b999("13074207");
    assert(b45 == b999);

    BigInt a7("5");
    BigInt k7("-3");
    BigInt c7 = a7 ^ k7;
    BigInt pepe("-6");
    assert(c7 == pepe);

    return 0;
}
