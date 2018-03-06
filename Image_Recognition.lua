require("torch")
require("nn")
require("paths")
--[[
    The steps of trainig model using torch library 
    我们来总结一下用torch神经网络的几个步骤：
    1.加载数据并对其预处理
    2.定义神经网络模型
    3.定义损失函数
    4.在训练集上训练网络
    5.在测试集上测试网络

]]
-- datasets preparation 
if (not paths.filep("cifar10torchsmall.zip")) then
    -- add shell command
    os.execute('wget -c https://s3.amazonaws.com/torch7/data/cifar10torchsmall.zip')
    os.execute('unzip cifar10torchsmall.zip')
end
trainset = torch.load('cifar10-train.t7')
testset = torch.load('cifar10-test.t7')
classes = {'airplane', 'automobile', 'bird', 'cat','deer', 'dog', 'frog', 'horse', 'ship', 'truck'}
print(trainset)
print(#trainset.data)

---Add size() function and Tensor index operator 
    setmetatable(trainset, 
    {__index = function(t, i) 
                    return {t.data[i], t.label[i]} 
                end}
);
trainset.data = trainset.data:double() 

function trainset:size() 
    return self.data:size(1) 
end

mean = {}
stdv = {}
for k = 1,3 do
    print(type(trainset.data[{ {}, {k}, {}, {}  }]))
    mean[k] = trainset.data[{ {}, {k}, {}, {}  }]:mean()
    break
    print('Channel '..k..',Mean: '..mean[k])
    trainset.data[{ {}, {k}, {}, {}  }]:add(-mean[k])
    stdv[k] = trainset.data[{ {}, {k}, {}, {}  }]:stdv()
    print('Channel '..k..',Standard Deviation: '..stdv[k])
    trainset.data[{{},{k},{},{}}]:dvi(stdv[k])
end

-- model defination 
net = nn.Sequential()
net:add(nn.SpatialConvolution(3,6,5,5))
net:add(nn.ReLU())
net:add(nn.SpatialMaxPooling(2,2,2,2))
net:add(nn.SpatialConvolution(6,16,5,5))
net:add(nn.ReLU())
net:add(nn.SpatialMaxPooling(2,2,2,2))
net:add(nn.View(16*5*5))
net:add(nn.Linear(16*5*5,120))
net:add(nn.ReLU())
net:add(nn.Linear(120,84))
net:add(nn.ReLU())
net:add(nn.Linear(84,10))
net:add(nn.LogSoftMax())

print('Lenet5\n' .. net:__tostring())

-- defination of criterion
criterion = nn.ClassNLLCriterion()

--train of the network 
trainer = nn.StochasticGradient(net,criterion)
trainer.learningRate = 0.001
-- the number of the training process
trainer.maxIteration = 5
trainer:train(trainset)
-- test data 
testset.data = testset.data:double()
for k=1,3 do
    testset.data[{{},{k},{},{}}]:add(-mean[k])
    testset.data[{{},{k},{},{}}]:div(stdv[k])
end
