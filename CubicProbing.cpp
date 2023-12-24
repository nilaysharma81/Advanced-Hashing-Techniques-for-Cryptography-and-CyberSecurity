#include "CubicProbing.h"
using namespace std;

void CubicProbing::merge(vector<int> &v, int l, int m, int r) {
  int a = m - l + 1;int b = r - m;
  vector<int> left(a);vector<int> right(b);
  for (int idx = 0; idx < b; idx++) {
    right[idx] = v[m + idx + 1];}
  for (int jdx = 0; jdx < a; jdx++) {
    left[jdx] = v[l + jdx];}
  int idx = 0;int jdx = 0;int kdx = l;
  while (idx < a && jdx < b) {
    if (left[idx] <= right[jdx]) {
      v[kdx] = left[idx];idx++;} else {
      v[kdx] = right[jdx];jdx++;}
    kdx++;
  }
  while (idx < a) {
    v[kdx] = left[idx];kdx++;idx++;}
  while (jdx < b) {
    v[kdx] = right[jdx];kdx++;jdx++;}
}

void CubicProbing::ms(vector<int> &v, int l, int r) {
  if (l < r && l >= 0 && r < v.size()) {
    int m = (r - l) / 2 + l;
    ms(v, l, m);ms(v, m + 1, r);merge(v, l, m, r);}
}

void CubicProbing::createAccount(string id, int count) {
  Account acc1;acc1.id = id;acc1.balance = count;dbs = dbs + 1;
  if (univ == true) {
    bankStorage1d.resize(200003);
    for(int i = 0; i <200003;i++){
      bankStorage1d[i].balance = -1;
    }
    univ = false;
    }
    
  int idx = hash(id);
  // while (doesExist(idx)==true){
  //  idx=idx+1;}
  // bankStorage1d[idx] = acc1;
  if (bankStorage1d[idx].id == "") {bankStorage1d[idx] = acc1;} else {
    long long int j = 1;
    for (long long int i = idx; i < bankStorage1d.size(); i = (i + j * j * j) % 200003) {
      if (bankStorage1d[i].id == "") {
        bankStorage1d[i] = acc1;
        break;
      }
      j++;
    }
  }
  // IMPLEMENT YOUR CODE HERE
}

vector<int> CubicProbing::getTopK(int k) {
  vector<int> v1;
  for (int i = 0; i < bankStorage1d.size(); i++) {
    if (bankStorage1d[i].id != "") {
      v1.push_back(bankStorage1d[i].balance);
    }
  }
  ms(v1, 0, dbs - 1);vector<int> TopK;
  for (int i = dbs - 1; i >= dbs - k && i>=0; i--) {TopK.push_back(v1[i]);}
  return TopK;
  // IMPLEMENT YOUR CODE HERE
  // Placeholder return value
}

int CubicProbing::getBalance(string id) {
  if (doesExist(id) == true) {
    int idx = hash(id);long long int j = 1;
    for (long long int i = idx; i < bankStorage1d.size(); i = (i + j * j * j) % 200003) {
      if (bankStorage1d[i].id == id) {return bankStorage1d[i].balance;}
      j++;
    }return -1;} else {
    return -1;}
  return -1;
  // IMPLEMENT YOUR CODE HERE
  // Placeholder return value
}

void CubicProbing::addTransaction(string id, int count) {
  if (doesExist(id) == false) {createAccount(id, count);} else {
    int idx = hash(id);long long int j = 1;
    for (long long int i = idx; i < bankStorage1d.size(); i = (i + j * j *j) % 200003) {
      if (bankStorage1d[i].id == id) {
        int b = bankStorage1d[i].balance;
        deleteAccount(bankStorage1d[i].id);
        createAccount(id, b + count);
        break;
      }
      j++;
    }
    // IMPLEMENT YOUR CODE HERE
  }
  // IMPLEMENT YOUR CODE HERE
}

bool CubicProbing::doesExist(string id) {
  int idx = hash(id);long long int j = 1;
  for (long long int i = idx; i < bankStorage1d.size(); i = (i + j * j * j) % 200003) {
    if (bankStorage1d[i].id == id) {
      return true;
      break;
    }
    else if (bankStorage1d[i].balance==-1){
      return false;
      break;
    }
        j++;
  }
  // IMPLEMENT YOUR CODE HERE
  return false;
}

bool CubicProbing::deleteAccount(string id) {
  if (doesExist(id) == false) {return false;} else {
    int idx = hash(id);long long int j = 1;
    for (long long int i = idx; i < bankStorage1d.size(); i = (i + j * j * j) % 200003) {
      if (bankStorage1d[i].id == id) {
        dbs = dbs - 1;bankStorage1d[i].balance = -6;bankStorage1d[i].id = "";  // resetting that id.
        return true;
      }
      j++;
    }
  }
  // IMPLEMENT YOUR CODE HERE
  return false;  // Placeholder return value
}
int CubicProbing::databaseSize() {
  // IMPLEMENT YOUR CODE HERE
  return dbs;  // Placeholder return value
}

int CubicProbing::hash(string id) {
  int hf = 0;int k = 1;
  for (char c : id) {hf = hf + k * (c+1);k++;}
  return hf % 100103;
  // IMPLEMENT YOUR CODE HERE
  return 0;  // Placeholder return value
}
