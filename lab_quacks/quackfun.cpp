/**
 * @file quackfun.cpp
 * This is where you will implement the required functions for the
 *  stacks and queues portion of the lab.
 */

namespace QuackFun {

/**
 * Sums items in a stack.
 * @param s A stack holding values to sum.
 * @return The sum of all the elements in the stack, leaving the original
 *  stack in the same state (unchanged).
 *
 * @note You may modify the stack as long as you restore it to its original
 *  values.
 * @note You may use only two local variables of type T in your function.
 *  Note that this function is templatized on the stack's type, so stacks of
 *  objects overloading the + operator can be summed.
 * @note We are using the Standard Template Library (STL) stack in this
 *  problem. Its pop function works a bit differently from the stack we
 *  built. Try searching for "stl stack" to learn how to use it.
 * @hint Think recursively!
 */
template <typename T>
T sum(stack<T>& s)
{
    T Sum;
    if(s.size() == 1) return s.top();
    else{
        T temp = s.top();
        s.pop();
        Sum = sum(s) + temp;
        s.push(temp);
    }
    // Your code here
    return Sum; // stub return value (0 for primitive types). Change this!
                // Note: T() is the default value for objects, and 0 for
                // primitive types
}

/**
 * Checks whether the given string (stored in a queue) has balanced brackets. 
 * A string will consist of 
 * square bracket characters, [, ], and other characters. This function will return
 * true if and only if the square bracket characters in the given
 * string are balanced. For this to be true,
 * all brackets must be matched up correctly, with no extra, hanging, or unmatched
 * brackets. For example, the string "[hello][]" is balanced, "[[][[]a]]" is balanced,
 * "[]]" is unbalanced, "][" is unbalanced, and "))))[cs225]" is balanced.
 *
 * You are allowed only the use of one stack in this function, and no other local variables.
 *
 * @param input The queue representation of a string to check for balanced brackets in
 * @return Whether the input string had balanced brackets
 */
bool isBalanced(queue<char> input)
{
    stack<char> output;
    int matched = 0;
    int left = 0;
    int right = 0;
    //extract all the brackets
    while(!input.empty()){
        if(input.front() == '[' || input.front() == ']')
            output.push(input.front());
    input.pop();
    }
    //check if they are matched
    while(!output.empty()){
        if(output.top() == '['){
            matched--;
            left++;
            if(matched < 0){
                return false;
            }
        }
        if(output.top() == ']'){
            right++;
            matched++;
        }
        //std::cout << output.top() << std::endl;
    output.pop();
    }
    if((left != right) || (matched != 0))return false;
    else return true;
}

/**
 * Reverses even sized blocks of items in the queue. Blocks start at size
 * one and increase for each subsequent block.
 * @param q A queue of items to be scrambled
 *
 * @note Any "leftover" numbers should be handled as if their block was
 *  complete.
 * @note We are using the Standard Template Library (STL) queue in this
 *  problem. Its pop function works a bit differently from the stack we
 *  built. Try searching for "stl stack" to learn how to use it.
 * @hint You'll want to make a local stack variable.
 */
template <typename T>
void scramble(queue<T>& q)
{
    stack<T> s;
    queue<T> q2;
    int swap = 2;
    int keep = 1;
    while(!q.empty()){
        for(int i = 0; i < keep; i++){
            if(q.empty()) break;
            q2.push(q.front());
            q.pop();
        }
        for(int j = 0; j < swap; j++){
            if(q.empty()) break;
            s.push(q.front());
            q.pop();
        }   
        while(!s.empty()){
            q2.push(s.top());
            s.pop();
        }
    swap += 2;
    keep += 2;    
    }
    q = q2;
}

/**
 * @return true if the parameter stack and queue contain only elements of
 *  exactly the same values in exactly the same order; false, otherwise.
 *
 * @note You may assume the stack and queue contain the same number of items!
 * @note The back of the queue corresponds to the top of the stack!
 * @note There are restrictions for writing this function.
 * - Your function may not use any loops
 * - In your function you may only declare ONE local boolean variable to use in
 *   your return statement, and you may only declare TWO local variables of
 *   parametrized type T to use however you wish.
 * - No other local variables can be used.
 * - After execution of verifySame, the stack and queue must be unchanged. Be
 *   sure to comment your code VERY well.
 */
template <typename T>
bool verifySame(stack<T>& s, queue<T>& q)
{
/* forgot that you cant use loops, but this otherwise works
    bool retval = true; // optional

    T temp1;
    T temp2;
    if ((s.size() == 1) && (s.top() == q.back())) return true;
    //std::cout << q.size() << std::endl;
    if(s.top() != q.back()) return false;
    else{
        T temp1 = s.top();
        s.pop();
        for(unsigned long i = 0; i < (q.size()-1); i++){
            temp2 = q.front();
            q.pop();
            q.push(temp2);
            //std::cout << i << std::endl;
        }
        retval = verifySame(s,q) && retval;
        s.push(temp1);
        //q.push(temp2);
    }

    return retval;
}
*/
    bool retval = true; // optional

    T temp1;
    if(s.empty()) return true; //base case
    else{
        T temp1 = s.top(); //temp1 holds the top of the stack
        s.pop();//remove the top stack element
        //recursive call checks if the 1 smaller stack and queue are the same
        //and that the front of bigger queue and top of bigger stack are the same.
        retval = verifySame(s,q) && (temp1 == q.front());
        //rebuilding the stack and queue
        s.push(temp1); //adds top element back onto stack.
        q.push(q.front()); //copies the front element to the back of the queue.
        q.pop(); //then actually removes the front element from the queue.
        return retval;
    }
}

}
