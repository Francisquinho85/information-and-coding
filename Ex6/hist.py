from matplotlib import pyplot as plt
def main():
  ac1 = []
  bc1 = []
  ac2 = []
  bc2 = []

  with open("outC1.txt") as fc1:
    linesc1 = fc1.readlines()
  for lc1 in linesc1:
    i1c1,i2c1 = lc1.strip().split('=>')
    ac1.append(i1c1)
    bc1.append((int)(i2c1))
      
  with open("outC2.txt") as fc2:
    linesc2 = fc2.readlines()
  for lc2 in linesc2:
    i1c2,i2c2 = lc2.strip().split('=>')
    ac2.append(i1c2)
    bc2.append((int)(i2c2))

  b_end1 = sum(bc1)
  print(b_end1)    
  b_end2 = sum(bc2) 
  print(b_end2)
      
  name = ["left channel","right channel"]
  end =[b_end1,b_end2]
  
  # print(a)
  #print(b)
  plt.style.use('ggplot')
  plt.bar(name,end)
  #plt.hist()
  plt.show()
if __name__ == "__main__":
  main()
  