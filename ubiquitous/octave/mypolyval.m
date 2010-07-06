function Y=mypolyval(coeff, X)
coeff = transpose(coeff);
coeff = rot90(coeff);
Y = polyval(coeff, X);
end

