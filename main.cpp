#include <cstdio>
#include <vector>

#include "perceptron.h"

using namespace std;

const int dim = 7;

bool f( vector< double > point ) {
    double res = 0;
    for( int i = 0; i < point.size(); i++ ) {
        res += ( double )( i * i - 3*i - 125 ) * point[ i ];
    }
    return res > 0;
}

int main( void ) {
    srand( time( NULL ) );
    perceptron net( dim );
    vector< pair< vector< double >, bool > > train_set;
    vector< vector< double > > test_set;
    for( int i = 0; i < 5000; i++ ) {
        vector< double > A;
        for( int j = 0; j < dim; j++ ) {
            double val = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/100.0)) - 50.0;
            A.push_back( val );
        }
        net.add_train( make_pair( A, f( A ) ) );
    }
    net.train();
    vector< vector< double > > test;
    for( int i = 0; i < 100; i++ ) {
        vector< double > A;
        for( int j = 0; j < dim; j++ ) {
            double val = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/100.0)) - 50.0;
            A.push_back( val );
        }
        test.push_back( A );
        net.add_test( A );
    }
    vector< bool > result = net.test();
    for( int i = 0; i < result.size(); i++ ) {
        cout << "result[ " << i << " ] = " << result[ i ] << ", class -> " << f( test[ i ] ) << endl;
        if( result[ i ] != f( test[ i ] ) ) {
            cout << "WRONG!\n";
            return 0;
        }
    }
    cout << "ALL PASSED!" << endl;
    return 0;
}
