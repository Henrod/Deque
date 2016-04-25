#include <iostream>
#include <stdexcept>

using namespace std;

class Deque {
	private:
		int* mDeque;
		int mCap;
		int mHead, mTail;
	public:
		enum End {head, tail};
		Deque(int cap);
		~Deque();
		void enqueue(End end, int data);
		int dequeue(End end);
		void print();
};

Deque::Deque(int cap) {
	mCap = cap;
	mDeque = new int [mCap];
	mHead = mTail = 0;
}

Deque::~Deque() {
	delete[] mDeque;
}

int Deque::dequeue(End end) {
	if (mTail - mHead <= 1) throw underflow_error("Empty deque");

	int pos;
	if (end == End::head) pos = (++mHead) % mCap;
	else pos = (--mTail) % mCap;

	if (pos < 0) pos += mCap;

	return mDeque[pos];
}
void Deque::enqueue(End end, int data) {
	if (mTail - mHead > mCap) throw overflow_error("Full deque");

	if (mHead == mTail) {
		mDeque[mHead] = data;
		--mHead;
		++mTail;
		return;
	}

	int pos;
	if (end == End::head) {
		pos = (mHead--) % mCap;
	} else {
		pos = (mTail++) % mCap;
	}

	if (pos < 0) pos += mCap;
	mDeque[pos] = data;
}

void Deque::print() {
	for (int i = mHead + 1; i < mTail; ++i) {
		int pos = i % mCap;
		if (pos < 0) pos += mCap;
		cout << mDeque[pos] << " ";
	}

	cout << endl;
}


int main() {
	cout << "Insert a command> " << endl;
	cout << "\teh <integer> (Enqueue head)" << endl;
	cout << "\tet <integer> (Enqueue tail)" << endl;
	cout << "\tdh (Dequeue head)" << endl;
	cout << "\tdt (Dequeue tail)" << endl;
	cout << "\ts (stop)" << endl;

	bool stop = false;
	Deque deque (5);

	while (!stop) {
		cout << "Command> ";
		string comm;
		cin >> comm;

		if (comm == "eh") {
			int data;
			cin >> data;
			try {
				deque.enqueue(Deque::head, data);
			} catch (const overflow_error& e) {
				cout << e.what() << endl;
			}
		} else if (comm == "et") {
			int data;
			cin >> data;
			try {
				deque.enqueue(Deque::tail, data);
			} catch (const overflow_error& e) {
				cout << e.what() << endl;
			}
		} else if (comm == "dh") {
			try {
				deque.dequeue(Deque::head);
			} catch (const underflow_error& e) {
				cout << e.what() << endl;
			}
		} else if (comm == "dt") {
			try {
				deque.dequeue(Deque::tail);
			} catch (const underflow_error& e) {
				cout << e.what() << endl;
			}
		} else if (comm == "s") {
			stop = true;
		} else {
			cout << "Wrong command, try again." << endl;
		}

		deque.print();
	}

	return 0;
}
