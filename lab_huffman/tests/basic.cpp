#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <fstream>
#include <unordered_map>

#include "binary_file_reader.h"
#include "decoder.h"
#include "encoder.h"
#include "huffman_tree.h"

using namespace std;

#define ADD_CHAR(c, freq) \
	do { \
		for( int i = 0; i < freq; ++i ) \
			text << c; \
	} while( 0 )

void buildText() {
	ofstream text( "text.txt" );
	ADD_CHAR( 'a', 20 );
	ADD_CHAR( 'b', 30 );
	ADD_CHAR( 'c', 60 );
	ADD_CHAR( 'd', 40 );
	text.close();
}

void buildText2() {
	ofstream text( "text.txt" );
    ADD_CHAR( 'a', 5 );
    ADD_CHAR( 'b', 6 );
    ADD_CHAR( 'c', 12 );
    ADD_CHAR( 'd', 13 );
    ADD_CHAR( 'e', 7 );
    ADD_CHAR( 'f', 8 );
	text.close();
}

void buildText( int start ) {
    ofstream text( "text.txt" );
    for( char c = 'a'; c < 'f'; ++c ) {
        ADD_CHAR( c, start );
        start *= 2;
    }
    text << endl;
    text.close();
}

void compareBinaryFiles( string yourFile, string ourFile ) {
	ifstream yourBinary( yourFile, ios::binary );
	stringstream yours;
	yours << yourBinary.rdbuf();
	ifstream ourBinary( ourFile, ios::binary );
	stringstream ours;
	ours << ourBinary.rdbuf();
	if( yours.str() != ours.str() )
		FAIL( "Your binary file \"" + yourFile + "\" does not match our binary file \"" + ourFile + "\"");
}

HuffmanTree constructTree( string inputFile ) {
	ifstream toEncode( inputFile );
	stringstream data;
	data << toEncode.rdbuf();
	string str(data.str());
	unordered_map<char, int> freqs;
	for( size_t i = 0; i < str.length(); ++i )
		freqs[str[i]]++;
	vector<Frequency> buildWith;
	for( auto it = freqs.begin(); it != freqs.end(); ++it )
		buildWith.push_back( Frequency( it->first, it->second ) );
	return HuffmanTree( buildWith );
}

TEST_CASE("test_encoder_binary", "[weight=1]") {
	buildText();
	std::cout << system("pwd") << std::endl;
	encoder::encodeFile( "text.txt", "Results/test.bin", "Results/tree.huff" );
	compareBinaryFiles( "Results/test.bin", "Solutions/soln_test.bin" );
}

TEST_CASE("test_encoder_binary2", "[weight=1]") {
	buildText2();
	encoder::encodeFile( "text.txt", "Results/test.bin", "Results/tree.huff" );
	compareBinaryFiles( "Results/test.bin", "Solutions/soln_test2.bin" );
}

TEST_CASE("test_encoder_writetree", "[weight=1]") {
	buildText();
	encoder::encodeFile( "text.txt", "Results/test.bin", "Results/tree.huff" );
	compareBinaryFiles( "Results/tree.huff", "Solutions/soln_tree.huff" );
}

TEST_CASE("test_encoder_writetree2", "[weight=1]") {
	buildText2();
	encoder::encodeFile( "text.txt", "Results/test.bin", "Results/tree.huff" );
	compareBinaryFiles( "Results/tree.huff", "Solutions/soln_tree2.huff" );
}

TEST_CASE("test_decode", "[weight=1]") {
	buildText();
	HuffmanTree htree = constructTree( "text.txt" );
	BinaryFileReader bfile( "Solutions/soln_test.bin" );
	string decoded = htree.decodeFile( bfile );
	ifstream in( "text.txt" );
	stringstream expected;
	expected << in.rdbuf();
	REQUIRE( expected.str() == decoded );
}

TEST_CASE("test_decode2", "[weight=1]") {
	buildText2();
	HuffmanTree htree = constructTree( "text.txt" );
	BinaryFileReader bfile( "Solutions/soln_test2.bin" );
	string decoded = htree.decodeFile( bfile );
	ifstream in( "text.txt" );
	stringstream expected;
	expected << in.rdbuf();
	REQUIRE( expected.str() == decoded );
}

TEST_CASE("test_decode_readtree", "[weight=1]") {
	buildText();
	decoder::decodeFile( "Solutions/soln_test.bin", "Solutions/soln_tree.huff", "Results/out.txt" );
	stringstream expected;
	stringstream decoded;
	ifstream expect( "text.txt" );
	expected << expect.rdbuf();
	ifstream out( "Results/out.txt" );
	decoded << out.rdbuf();
	REQUIRE( expected.str() == decoded.str() );
}

TEST_CASE("test_decode_readtree2", "[weight=1]") {
	buildText2();
	decoder::decodeFile( "Solutions/soln_test2.bin", "Solutions/soln_tree2.huff", "Results/out.txt" );
	stringstream expected;
	stringstream decoded;
	ifstream expect( "text.txt" );
	expected << expect.rdbuf();
	ifstream out( "Results/out.txt" );
	decoded << out.rdbuf();
	REQUIRE( expected.str() == decoded.str() );
}

TEST_CASE("test_the_works", "[weight=1]") {
    buildText( 2 );
    encoder::encodeFile( "text.txt", "Results/test.bin", "Results/tree.huff" );
    decoder::decodeFile( "Results/test.bin", "Results/tree.huff", "Results/out.txt" );
    stringstream expected;
    stringstream decoded;
    ifstream expect( "test.txt" );
    expected << expect.rdbuf();
    ofstream out( "Results/out.txt" );
    decoded << out.rdbuf();
    REQUIRE( expected.str() == decoded.str() );
    compareBinaryFiles( "Results/tree.huff", "Solutions/soln_tree_2.huff" );
    compareBinaryFiles( "Results/test.bin", "Solutions/soln_test_2.bin" );
}
