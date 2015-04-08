package main

import (
	"fmt"
	"math/rand"
)

func main() {
	for people:=2; people < 35; people++ {
		numberTries := 10000
		triesWithClash := 0
		for j:=0 ; j<numberTries; j++ {
			// Create map with whether birthday has been taken or not
			// birthday: day_taken
			birthdays_taken := make(map[int]bool)
			for i := 1; i<=365; i++ {
				birthdays_taken[i] = false
			}
			// Create people new birthdays and check whether there is a clash
			for j := 1; j<=people; j++ {
				newBirthday := rand.Intn(365) + 1

				if birthdays_taken[newBirthday] == true {
					// Birthday has already been taken we have a clash!
					triesWithClash += 1
					// We must break here. We cant have more triesWithClash than numberTries!
					break
				} else {
					// Set birthday to be taken
					birthdays_taken[newBirthday] = true
				}
			}
		}
		percentageClash := (float64(triesWithClash) / float64(numberTries)) * 100
		fmt.Printf("Number party goers: %d, Probability of Birthday Clash: %f %%\n", people,percentageClash)
	}
}