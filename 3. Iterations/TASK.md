#Task

1. Given an integer n, for all values from 0 -> n calculate both n! and the nth Fibonacci number
2. Display PI correct to n decimal places using Leibniz series

Bonus : What is the fastest we can calculate PI to 10dps still using Leibniz series? What are some pitfalls?

Notes :
 - Turns out Leibniz series for PI converges very slowly. It takes 1bn iterations just to get 10dps!
 - How do we know correct to n dps? Assume correct if doesn't change in next iteration. (While I won't do a mathematical proof, this is a valid assumption for the Leibniz convergence.)
 - Use ```time ./file``` to measure time elapsed
