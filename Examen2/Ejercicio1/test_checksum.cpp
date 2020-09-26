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
    CHECK( Checksum::compute("Hello World") == 0xd60dd805 );
    CHECK( Checksum::compute("Hola Mundo") == 0x32d3fe11 );
    CHECK( Checksum::compute("CARLOS JOSE CONTRERAS RIVERA") == 0xdf1e032b );
    CHECK( Checksum::compute("LEONEL ALBERTO THOMAS VILLALOBOS") == 0x96def6a2 );
    CHECK( Checksum::compute("BILANDER FERNANDEZ EWENS") == 0x644b6c3f );
    CHECK( Checksum::compute("SELVIN RAUL RODRIGUEZ GIRON") == 0xda111838 );
    CHECK( Checksum::compute("GABRIELA PAOLA DIAZ REYNAUD") == 0x260c184c );
}