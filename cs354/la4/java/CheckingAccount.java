public class CheckingAccount extends Account {

	public CheckingAccount(String number, Customer customer, double balance) {
		this.number = number;
		this.customer = customer;
		this.balance = balance;
	}

	@Override
	public void accrue(double rate) { }

}
