#ifndef CAFFE_CUDNN_RELU_LAYER_HPP_
#define CAFFE_CUDNN_RELU_LAYER_HPP_

#include <vector>

#include "caffe/blob.hpp"
#include "caffe/layer.hpp"
#include "caffe/proto/caffe.pb.h"

#include "caffe/layers/neuron_layer.hpp"
#include "caffe/layers/relu_layer.hpp"

namespace caffe
{

#ifdef USE_CUDNN
/**
 * @brief CuDNN acceleration of ReLULayer.
 */
template <typename Ftype, typename Btype>
class CuDNNReLULayer : public ReLULayer<Ftype, Btype>
{
public:
    explicit CuDNNReLULayer(const LayerParameter &param)
        : ReLULayer<Ftype, Btype>(param), handles_setup_(false) {}
    virtual void LayerSetUp(const vector<Blob *> &bottom,
                            const vector<Blob *> &top);
    virtual void Reshape(const vector<Blob *> &bottom,
                         const vector<Blob *> &top);
    virtual ~CuDNNReLULayer();

protected:
    virtual void Forward_gpu(const vector<Blob *> &bottom,
                             const vector<Blob *> &top);
    virtual void Backward_gpu(const vector<Blob *> &top,
                              const vector<bool> &propagate_down, const vector<Blob *> &bottom);

    bool handles_setup_;
    cudnnTensorDescriptor_t fwd_bottom_desc_, bwd_bottom_desc_;
    cudnnTensorDescriptor_t fwd_top_desc_, bwd_top_desc_;
    cudnnActivationDescriptor_t activ_desc_;
};
#endif

} // namespace caffe

#endif // CAFFE_CUDNN_RELU_LAYER_HPP_
