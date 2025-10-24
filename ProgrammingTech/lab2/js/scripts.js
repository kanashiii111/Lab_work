// Базовый скрипт для демонстрации работы формы
document.getElementById('bookingForm').addEventListener('submit', function(e) {
    e.preventDefault();
    
    const matchValue = document.getElementById('match').value;
    const ticketType = document.getElementById('ticketType').value;
    const quantity = document.getElementById('quantity').value;
    const email = document.getElementById('email').value;

    const matchNames = {
        'match1': 'OKC Thunder vs Minnesota Timberwolves',
        'match2': 'Miami Heat vs LA Lakers', 
        'match3': 'Sacramento Kings vs Washington Wizards'
    };
    
    const ticketTypes = {
        'standard': 'Стандарт',
        'premium': 'Премиум', 
        'vip': 'VIP'
    };

    // Получаем человекочитаемое название матча
    const matchDisplayName = matchNames[matchValue] || matchValue;
    const ticketDisplayName = ticketTypes[ticketType] || ticketType;
    
    const ordersList = document.getElementById('ordersList');
    const noOrders = ordersList.querySelector('.no-orders');
    
    if (noOrders) {
        noOrders.style.display = 'none';
    }
    
    const orderItem = document.createElement('div');
    orderItem.className = 'order-card';
    orderItem.innerHTML = `
        <div class="order-header">
            <div class="order-match">${matchDisplayName}</div>
        </div>
        <div class="order-details">
            <div><strong>Тип билета:</strong> ${ticketDisplayName}</div>
            <div><strong>Количество:</strong> ${quantity}</div>
            <div><strong>Email:</strong> ${email}</div>
        </div>
    `;
    
    ordersList.appendChild(orderItem);
    this.reset();
    
    alert('Билет успешно забронирован!');
});