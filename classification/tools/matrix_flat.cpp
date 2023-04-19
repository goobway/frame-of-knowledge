#include <iostream>
#include <Eigen/Dense>

int main() {
  unsigned char matrix[2][3] = {{1, 2, 3}, {4, 5, 6}};
  Eigen::MatrixXi intMatrix = Eigen::Map<Eigen::Matrix<unsigned char, Eigen::Dynamic, Eigen::Dynamic>>(matrix, 2, 3).cast<int>();
  Eigen::VectorXd flattened = Eigen::Map<Eigen::VectorXd>(intMatrix.data(), intMatrix.size());

  std::cout << "Original matrix:\n" << intMatrix << "\n\n";
  std::cout << "Flattened vector:\n" << flattened.transpose() << "\n";
}
