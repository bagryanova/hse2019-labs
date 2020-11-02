#include "shared_ptr.hpp"
#include <cassert>

shared_ptr::Storage::Storage(Matrix* mtr) :
        data_(mtr), ref_count_(1) {}

shared_ptr::Storage::~Storage() {
    delete data_;
}

void shared_ptr::Storage::incr() {
    ++ref_count_;
}

void shared_ptr::Storage::decr() {
    assert(ref_count_ > 0);
    --ref_count_;
}

int shared_ptr::Storage::getCounter() const {
    return ref_count_;
}

Matrix* shared_ptr::Storage::getObject() const {
    assert(data_ != nullptr);
    return data_;
}

shared_ptr::shared_ptr(Matrix* obj) {
    get_new_storage(obj);
}

shared_ptr::shared_ptr(const shared_ptr& other) {
    storage_ = other.storage_;
    if (!isNull()) {
        storage_->incr();
    }
}

void shared_ptr::dec_storage() {
    if (isNull()) {
        return;
    }
    storage_->decr();
    if (storage_->getCounter() == 0) {
        delete storage_;
    }
}

shared_ptr& shared_ptr::operator=(shared_ptr other) {
    dec_storage();
    storage_ = other.storage_;
    if (!isNull()) {
        storage_->incr();
    }
    return *this;
}

shared_ptr::~shared_ptr() {
    dec_storage();
}

Matrix* shared_ptr::ptr() const {
    if (isNull()) {
        return nullptr;
    }
    return storage_->getObject();
}

bool shared_ptr::isNull() const {
    return storage_ == nullptr;
}

void shared_ptr::reset(Matrix* obj) {
    dec_storage();
    get_new_storage(obj);
}

void shared_ptr::get_new_storage(Matrix* obj) {
    if (obj == nullptr) {
        storage_ = nullptr;
    } else {
        storage_ = new Storage(obj);
    }
}

Matrix* shared_ptr::operator->() const {
    return ptr();
}

Matrix& shared_ptr::operator*() const {
    assert(!isNull());
    return *(ptr());
}

