package assignment4;

public class Transaction extends Balance {
	///constructor to initialize data members and validate class invariants
	public Transaction(double bal) {
		super(bal);
	}
	///member function to withdraw amount
	public void withdraw(double amount) throws Exception {
		if(balance < amount)
			throw new Exception("insufficient balance");
		if(balance<0)
			System.out.println("Wrong input");
		balance -= amount;
		update();
	}
	///member function to deposit amount
	public void deposit(double amount) {
		if(balance<0)
			System.out.println("Wrong input");
		balance += amount;
		update();
	}
}
