public class MatrixAdder {
    // Method to add two matrices
    public static List<List<Integer>> addMatrices(List<List<Integer>> matrix1, List<List<Integer>> matrix2) {
        // Validate input matrices
        if (matrix1 == null || matrix2 == null || matrix1.isEmpty() || matrix2.isEmpty()) {
            throw new MatrixException('Matrices cannot be null or empty.');
        }
        
        // Get dimensions
        Integer rows1 = matrix1.size();
        Integer cols1 = matrix1[0].size();
        Integer rows2 = matrix2.size();
        Integer cols2 = matrix2[0].size();
        
        // Validate dimensions
        if (rows1 != rows2 || cols1 != cols2) {
            throw new MatrixException('Matrices must have the same dimensions for addition.');
        }
        
        // Validate row lengths are consistent
        for (List<Integer> row : matrix1) {
            if (row.size() != cols1) {
                throw new MatrixException('Inconsistent row lengths in matrix1.');
            }
        }
        for (List<Integer> row : matrix2) {
            if (row.size() != cols2) {
                throw new MatrixException('Inconsistent row lengths in matrix2.');
            }
        }
        
        // Initialize result matrix
        List<List<Integer>> result = new List<List<Integer>>();
        
        // Perform matrix addition
        for (Integer i = 0; i < rows1; i++) {
            List<Integer> resultRow = new List<Integer>();
            for (Integer j = 0; j < cols1; j++) {
                resultRow.add(matrix1[i][j] + matrix2[i][j]);
            }
            result.add(resultRow);
        }
        
        return result;
    }
    
    // Custom exception class for matrix errors
    public class MatrixException extends Exception {}
}