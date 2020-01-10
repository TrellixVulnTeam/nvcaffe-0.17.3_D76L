#ifndef CAFFE_DUMMY_DATA_LAYER_HPP_
#define CAFFE_DUMMY_DATA_LAYER_HPP_

#include <vector>

#include "caffe/blob.hpp"
#include "caffe/filler.hpp"
#include "caffe/layer.hpp"
#include "caffe/proto/caffe.pb.h"

namespace caffe
{

/**
 * @brief Provides data to the Net generated by a Filler.
 *
 * TODO(dox): thorough documentation for Forward and proto params.
 */
template <typename Ftype, typename Btype>
class DummyDataLayer : public Layer<Ftype, Btype>
{
public:
    explicit DummyDataLayer(const LayerParameter &param)
        : Layer<Ftype, Btype>(param) {}
    virtual void LayerSetUp(const vector<Blob *> &bottom,
                            const vector<Blob *> &top);
    // Data layers should be shared by multiple solvers in parallel
    virtual inline bool ShareInParallel() const { return true; }
    // Data layers have no bottoms, so reshaping is trivial.
    virtual void Reshape(const vector<Blob *> &bottom,
                         const vector<Blob *> &top) {}

    virtual inline const char *type() const { return "DummyData"; }
    virtual inline int ExactNumBottomBlobs() const { return 0; }
    virtual inline int MinTopBlobs() const { return 1; }

protected:
    virtual void Forward_cpu(const vector<Blob *> &bottom,
                             const vector<Blob *> &top);
    virtual void Backward_cpu(const vector<Blob *> &top,
                              const vector<bool> &propagate_down, const vector<Blob *> &bottom) {}
    virtual void Backward_gpu(const vector<Blob *> &top,
                              const vector<bool> &propagate_down, const vector<Blob *> &bottom) {}

    vector<shared_ptr<Filler<Ftype>>> fillers_;
    vector<bool> refill_;
};

} // namespace caffe

#endif // CAFFE_DUMMY_DATA_LAYER_HPP_
