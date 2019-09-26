#include <vector>
#include <ctime>
#include <cstdlib>
#include <iostream>

using namespace std;

class perceptron {
    public:
        perceptron( int N );
        void train( const double a = 0.2 ); // standard value for learning factor
        double combine( const vector< double >& data );
        void add_train( pair< vector< double >, bool > new_data ) { train_set.push_back( new_data ); }
        void add_test( vector< double > new_data ) { test_set.push_back( new_data ); }
        void clear() { train_set.clear(); test_set.clear(); }
        vector< bool > test();
        friend ostream& operator << ( ostream& out, const perceptron& P );
    protected:
        int n_input;
        vector< pair< vector< double >, bool > > train_set;
        vector< vector< double > > test_set;
        vector< double > weights;
};

perceptron::perceptron( int N ) {
    srand( time( NULL ) );
    n_input = N;
    for( int i = 0; i <= n_input; i++ ) {
        double initial_weight = ( double )rand() / RAND_MAX;
        weights.push_back( initial_weight );
    }
}

ostream& operator << ( ostream& out, const perceptron& P ) {
    out << "Perceptron network with number of inputs: " << P.n_input << endl;
    out << "Weight vector: (";
    for( int i = 0; i <= P.n_input; i++ ) {
        out << P.weights[ i ];
        if( i != P.n_input ) out << ",";
    }
    out << ")" << endl;
    return out;
}

double perceptron::combine( const vector< double >& data ) {
    double result = this->weights[ 0 ];
    for( int i = 1; i <= n_input; i++ ) {
        result += this->weights[ i ] * data[ i - 1 ];
    }
    return result;
}

void perceptron::train( const double a ) {
    bool changed;
    do {
        changed = false;
        for( auto data : train_set ) {
            vector< double > point = data.first;
            double data_class = data.second ? -1 : 1;
            double output = combine( point );
            if( output * data_class < 0 ) { //if misclassified
                changed = true;
                double y = output > 0 ? 1 : -1;
                double factor = a * ( data_class - y );
                weights[ 0 ] += factor;
                for( int i = 1; i <= this->n_input; i++ ) {
                    weights[ i ] += factor * point[ i - 1 ];
                }
            }
        }
    } while( changed );
}

vector< bool > perceptron::test() {
    vector< bool > eval;
    for( auto data : test_set ) {
        double res = combine( data );
        eval.push_back( res > 0 ? 0 : 1 );
    }
    return eval;
}
