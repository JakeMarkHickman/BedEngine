#pragma once

#include <functional>
#include <unordered_map>
#include <mutex>

namespace Bed
{
    template <typename payload>
    class Event
    {
    public:

        uint64_t Subscribe(std::function<void(payload)> listner) 
        {
            std::lock_guard<std::mutex> lock(m_Mutex);

            uint64_t curListner;

            if(!m_RemovedListners.empty())
            {
                curListner = m_RemovedListners.back(); //use std::queue to remove from front and add to back.
                m_RemovedListners.pop_back();

                return curListner;
            }
            else
            {
                curListner = m_NextListnerId;
                m_NextListnerId++;
            }
            
            m_Listners.emplace(curListner, listner);
            
            return curListner;
        };

        void Unsubscribe(uint64_t listnerID) 
        {
            std::lock_guard<std::mutex> lock(m_Mutex);

            m_Listners.erase(listnerID);
            m_RemovedListners.emplace(listnerID);
        };

        void Broadcast(payload data) 
        {
            std::lock_guard<std::mutex> lock(m_Mutex);
            for(const auto& [id, listner] : m_Listners)
            {
                try {
                    listner(data);
                } catch (const std::exception& e) {
                    //std::cerr << "Listener " << id << " threw an exception: " << e.what() << '\n';
                } 
            }
        };

    private:
        std::unordered_map<uint64_t, std::function<void(payload)>> m_Listners;
        uint64_t m_NextListnerId = 0;
        std::vector<uint64_t> m_RemovedListners;
        std::mutex m_Mutex;
    };
}