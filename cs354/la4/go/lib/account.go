package lib

/*
Account interfaces and structs, along with standard functionality for accounts.
*/

import "fmt"

type IAccount interface {
	Balance() float64
	Deposit(float64)
	Withdraw(float64)
	String() string
	Accrue(chan float64, float64)
}

type Account struct {
	number   string
	customer *Customer
	balance  float64
}

func (a *Account) Balance() float64 {
	return a.balance
}

func (a *Account) Deposit(amount float64) {
	a.balance += amount
}

func (a *Account) Withdraw(amount float64) {
	a.balance -= amount
}

func (a *Account) String() string {
	return fmt.Sprintf(
		"%s:%s:%.1f",
		a.number,
		a.customer.String(),
		a.balance,
	)
}
