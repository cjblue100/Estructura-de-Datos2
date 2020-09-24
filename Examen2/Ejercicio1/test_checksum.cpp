#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <sstream>
#include <string>
#include "doctest.h"
#include "checksum.h"

TEST_CASE("Checksum: Strings with lenght < 4")
{
    CHECK( Checksum::compute("HO") == 0xb7b0dfe0 );
    CHECK( Checksum::compute("ED2") == 0xbabbcde0 );
}

TEST_CASE("Checksum: Strings with lenght > 4")
{
    CHECK( Checksum::compute("Hello World") == 0xb79a9394 );
    CHECK( Checksum::compute("Hola Mundo") == 0xb790939f );
    CHECK( Checksum::compute("CARLOS JOSE CONTRERAS RIVERA") == 0x6d6b8d6a );
    CHECK( Checksum::compute("LEONEL ALBERTO THOMAS VILLALOBOS") == 0x6e6e9071 );
    CHECK( Checksum::compute("BILANDER FERNANDEZ EWENS") == 0x6f726e6d );
    CHECK( Checksum::compute("SELVIN RAUL RODRIGUEZ GIRON") == 0x636c9358 );
    CHECK( Checksum::compute("GABRIELA PAOLA DIAZ REYNAUD") == 0x6f79716d );
}