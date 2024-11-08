package main

import (
	"bank/lib"
	"fmt"
)

func main() {
	bank := lib.NewBank()
	c := lib.NewCustomer("Ann")
	bank.Add(lib.NewCheckingAccount("01001", c, 100.00))
	bank.Add(lib.NewSavingAccount("01002", c, 200.00))
	bank.Accrue(0.02)
	fmt.Printf("%s\n", bank.String())
}