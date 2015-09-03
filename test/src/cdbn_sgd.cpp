//=======================================================================
// Copyright (c) 2014-2015 Baptiste Wicht
// Distributed under the terms of the MIT License.
// (See accompanying file LICENSE or copy at
//  http://opensource.org/licenses/MIT)
//=======================================================================

#include "catch.hpp"

#include "dll/conv_layer.hpp"
#include "dll/dense_layer.hpp"
#include "dll/conv_rbm.hpp"
#include "dll/dbn.hpp"
#include "dll/scale_layer.hpp"
#include "dll/mp_layer.hpp"
#include "dll/avgp_layer.hpp"
#include "dll/stochastic_gradient_descent.hpp"

#include "mnist/mnist_reader.hpp"
#include "mnist/mnist_utils.hpp"

TEST_CASE( "cdbn/sgd/1", "[dbn][mnist][sgd]" ) {
    typedef dll::dbn_desc<
        dll::dbn_layers<
            dll::conv_rbm_desc_square<1, 28, 10, 12, dll::momentum, dll::batch_size<10>, dll::weight_type<float>>::rbm_t,
            dll::rbm_desc<12 * 12 * 10, 10, dll::momentum, dll::batch_size<10>, dll::hidden<dll::unit_type::SOFTMAX>>::rbm_t
            >
        , dll::trainer<dll::sgd_trainer>
        , dll::batch_size<10>
        >::dbn_t dbn_t;

    auto dataset = mnist::read_dataset_direct<std::vector, etl::fast_dyn_matrix<float, 1, 28, 28>>(500);
    REQUIRE(!dataset.training_images.empty());

    mnist::binarize_dataset(dataset);

    auto dbn = std::make_unique<dbn_t>();

    dbn->pretrain(dataset.training_images, 20);

    auto ft_error = dbn->fine_tune(dataset.training_images, dataset.training_labels, 50);
    std::cout << "ft_error:" << ft_error << std::endl;
    CHECK(ft_error < 5e-2);

    auto test_error = dll::test_set(dbn, dataset.test_images, dataset.test_labels, dll::predictor());
    std::cout << "test_error:" << test_error << std::endl;
    REQUIRE(test_error < 0.2);
}

TEST_CASE( "cdbn/sgd/2", "[dbn][mnist][sgd]" ) {
    typedef dll::dbn_desc<
        dll::dbn_layers<
            dll::conv_rbm_desc_square<1, 28, 10, 12, dll::momentum, dll::batch_size<10>, dll::weight_type<float>>::rbm_t,
            dll::conv_rbm_desc_square<10, 12, 6, 6, dll::momentum, dll::batch_size<10>, dll::weight_type<float>>::rbm_t,
            dll::rbm_desc<6 * 6 * 6, 10, dll::momentum, dll::batch_size<10>, dll::hidden<dll::unit_type::SOFTMAX>>::rbm_t
            >
        , dll::trainer<dll::sgd_trainer>
        , dll::batch_size<10>
        >::dbn_t dbn_t;

    auto dataset = mnist::read_dataset_direct<std::vector, etl::fast_dyn_matrix<float, 1, 28, 28>>(500);
    REQUIRE(!dataset.training_images.empty());

    mnist::binarize_dataset(dataset);

    auto dbn = std::make_unique<dbn_t>();

    dbn->pretrain(dataset.training_images, 20);

    auto ft_error = dbn->fine_tune(dataset.training_images, dataset.training_labels, 50);
    std::cout << "ft_error:" << ft_error << std::endl;
    CHECK(ft_error < 5e-2);

    auto test_error = dll::test_set(dbn, dataset.test_images, dataset.test_labels, dll::predictor());
    std::cout << "test_error:" << test_error << std::endl;
    REQUIRE(test_error < 0.2);
}

TEST_CASE( "cdbn/sgd/3", "[dbn][mnist][sgd]" ) {
    typedef dll::dbn_desc<
        dll::dbn_layers<
            dll::conv_rbm_desc_square<1, 28, 10, 20, dll::momentum, dll::batch_size<10>, dll::weight_type<float>>::rbm_t,
            dll::conv_rbm_desc_square<10, 20, 10, 14, dll::momentum, dll::batch_size<10>, dll::weight_type<float>>::rbm_t,
            dll::rbm_desc<10 * 14 * 14, 700, dll::momentum, dll::batch_size<10>>::rbm_t,
            dll::rbm_desc<700, 10, dll::momentum, dll::batch_size<10>, dll::hidden<dll::unit_type::SOFTMAX>>::rbm_t
            >
        , dll::trainer<dll::sgd_trainer>
        , dll::batch_size<10>
        >::dbn_t dbn_t;

    auto dataset = mnist::read_dataset_direct<std::vector, etl::fast_dyn_matrix<float, 1, 28, 28>>(500);
    REQUIRE(!dataset.training_images.empty());

    mnist::binarize_dataset(dataset);

    auto dbn = std::make_unique<dbn_t>();

    dbn->pretrain(dataset.training_images, 20);

    auto ft_error = dbn->fine_tune(dataset.training_images, dataset.training_labels, 50);
    std::cout << "ft_error:" << ft_error << std::endl;
    CHECK(ft_error < 5e-2);

    auto test_error = dll::test_set(dbn, dataset.test_images, dataset.test_labels, dll::predictor());
    std::cout << "test_error:" << test_error << std::endl;
    REQUIRE(test_error < 0.2);
}

TEST_CASE( "cdbn/sgd/4", "[dbn][mnist][sgd]" ) {
    typedef dll::dbn_desc<
        dll::dbn_layers<
            dll::scale_layer_desc<1, 256>::layer_t,
            dll::conv_rbm_desc_square<1, 28, 10, 20, dll::momentum, dll::batch_size<10>, dll::weight_type<float>>::rbm_t,
            dll::conv_rbm_desc_square<10, 20, 10, 14, dll::momentum, dll::batch_size<10>, dll::weight_type<float>>::rbm_t,
            dll::rbm_desc<10 * 14 * 14, 700, dll::momentum, dll::batch_size<10>>::rbm_t,
            dll::rbm_desc<700, 10, dll::momentum, dll::batch_size<10>, dll::hidden<dll::unit_type::SOFTMAX>>::rbm_t
            >
        , dll::trainer<dll::sgd_trainer>
        , dll::batch_size<10>
        >::dbn_t dbn_t;

    auto dataset = mnist::read_dataset_direct<std::vector, etl::fast_dyn_matrix<float, 1, 28, 28>>(500);
    REQUIRE(!dataset.training_images.empty());

    auto dbn = std::make_unique<dbn_t>();

    dbn->pretrain(dataset.training_images, 20);

    auto ft_error = dbn->fine_tune(dataset.training_images, dataset.training_labels, 50);
    std::cout << "ft_error:" << ft_error << std::endl;
    CHECK(ft_error < 5e-2);

    auto test_error = dll::test_set(dbn, dataset.test_images, dataset.test_labels, dll::predictor());
    std::cout << "test_error:" << test_error << std::endl;
    REQUIRE(test_error < 0.2);
}

TEST_CASE( "lenet_rbm", "[dbn][mnist][sgd]" ) {
    typedef dll::dbn_desc<
        dll::dbn_layers<
            dll::scale_layer_desc<1, 256>::layer_t,
            dll::conv_rbm_desc_square<1, 28, 20, 24, dll::hidden<dll::unit_type::BINARY>, dll::momentum, dll::batch_size<10>, dll::weight_type<float>>::rbm_t,
            dll::mp_layer_3d_desc<20, 24, 24, 1, 2, 2, dll::weight_type<float>>::layer_t,
            dll::conv_rbm_desc_square<20, 12, 50, 8, dll::hidden<dll::unit_type::BINARY>, dll::momentum, dll::batch_size<10>, dll::weight_type<float>>::rbm_t,
            dll::mp_layer_3d_desc<50, 8, 8, 1, 2, 2, dll::weight_type<float>>::layer_t,
            dll::rbm_desc<50 * 4 * 4, 500, dll::hidden<dll::unit_type::BINARY>, dll::momentum, dll::batch_size<10>>::rbm_t,
            dll::rbm_desc<500, 10, dll::momentum, dll::batch_size<10>, dll::hidden<dll::unit_type::SOFTMAX>>::rbm_t
            >
        , dll::trainer<dll::sgd_trainer>
        , dll::momentum
        , dll::weight_decay<>
        , dll::batch_size<25>
        >::dbn_t dbn_t;

    auto dataset = mnist::read_dataset_direct<std::vector, etl::fast_dyn_matrix<float, 1, 28, 28>>(1000);
    REQUIRE(!dataset.training_images.empty());

    auto dbn = std::make_unique<dbn_t>();

    dbn->l2_weight_cost = 0.0005;
    dbn->initial_momentum = 0.9;
    dbn->final_momentum = 0.9;
    dbn->learning_rate = 0.1;

    dbn->pretrain(dataset.training_images, 20);

    auto ft_error = dbn->fine_tune(dataset.training_images, dataset.training_labels, 50);
    std::cout << "ft_error:" << ft_error << std::endl;
    CHECK(ft_error < 5e-2);

    auto test_error = dll::test_set(dbn, dataset.test_images, dataset.test_labels, dll::predictor());
    std::cout << "test_error:" << test_error << std::endl;
    REQUIRE(test_error < 0.2);
}

TEST_CASE( "lenet_mix", "[dbn][mnist][sgd]" ) {
    typedef dll::dbn_desc<
        dll::dbn_layers<
            dll::scale_layer_desc<1, 256>::layer_t,
            dll::conv_rbm_desc_square<1, 28, 20, 24, dll::hidden<dll::unit_type::RELU>, dll::momentum, dll::batch_size<10>, dll::weight_type<float>>::rbm_t,
            dll::mp_layer_3d_desc<20, 24, 24, 1, 2, 2, dll::weight_type<float>>::layer_t,
            //dll::conv_rbm_desc_square<20, 12, 50, 8, dll::hidden<dll::unit_type::BINARY>, dll::momentum, dll::batch_size<10>, dll::weight_type<float>>::rbm_t,
            dll::conv_desc<20, 12, 12, 50, 8, 8, dll::activation<dll::function::RELU>>::layer_t,
            dll::mp_layer_3d_desc<50, 8, 8, 1, 2, 2, dll::weight_type<float>>::layer_t,
            dll::rbm_desc<50 * 4 * 4, 500, dll::hidden<dll::unit_type::RELU>, dll::momentum, dll::batch_size<10>>::rbm_t,
            //dll::rbm_desc<500, 10, dll::momentum, dll::batch_size<10>, dll::hidden<dll::unit_type::SOFTMAX>>::rbm_t
            dll::dense_desc<500, 10, dll::activation<dll::function::SOFTMAX>>::layer_t
            >
        , dll::trainer<dll::sgd_trainer>
        , dll::momentum
        , dll::weight_decay<>
        , dll::batch_size<25>
        >::dbn_t dbn_t;

    auto dataset = mnist::read_dataset_direct<std::vector, etl::fast_dyn_matrix<float, 1, 28, 28>>(1000);
    REQUIRE(!dataset.training_images.empty());

    auto dbn = std::make_unique<dbn_t>();

    dbn->l2_weight_cost = 0.0005;
    dbn->initial_momentum = 0.9;
    dbn->final_momentum = 0.9;
    dbn->learning_rate = 0.01;

    dbn->pretrain(dataset.training_images, 20);

    auto ft_error = dbn->fine_tune(dataset.training_images, dataset.training_labels, 50);
    std::cout << "ft_error:" << ft_error << std::endl;
    CHECK(ft_error < 5e-2);

    auto test_error = dll::test_set(dbn, dataset.test_images, dataset.test_labels, dll::predictor());
    std::cout << "test_error:" << test_error << std::endl;
    REQUIRE(test_error < 0.2);
}
