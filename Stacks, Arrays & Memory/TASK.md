# TASK

1. Make an RPNsolver that takes a string of numbers and operators(+,-,/,*) and outputs the result.
2. Extend the supported numbers to include floats, 'pi' and 'e'
3. Extend the supported operators with 'sum', 'log', '^', 'sin', 'cos', '!'
4. Add stack operators 'push', '<>', '>>', '<<'


Solve these examples to verify equivalence: (Answer === Algerbraic === RPN)

        1 === 5 / ( 4 + ( 3 - ( 2 * 1 ) ) )                             === '5 4 3 2 1 / + - *'
        2 === ( ( Sin( Pi / 4 ) ) ^ 2 ) * 4                             === 'pi 4 / sin 2 ^ 4 *'
        3 === 1 / ( ( Sin( Pi / Fact(3) ) / Cos( Pi / Fact(3) ) ) ^ 2 ) === '1 pi 3 ! / push sin <> cos / 2 ^ /'
        4 ===
        0 - ( Sin( 1 * Pi / ( 1 + 1 ) ) + ( 1 + 1 ) * Cos( ( 1 + 1 ) * Pi / ( 1 + 1 ) ) + ( 1 + 1 + 1 ) * Sin( ( 1 + 1 + 1 ) * Pi / ( 1 + 1 ) ) + ( 1 + 1 + 1 + 1 ) * Cos( ( 1 + 1 + 1 + 1 ) * Pi / ( 1 + 1 ) ) )
        'pi 1 1 + / push push push sin >> 1 1 + push * cos * >> 1 1 1 + + push * sin * >> 1 1 1 1 + + + push * cos * sum 0 <> -'

Admittedly, the fourth one is somewhat contrived....
